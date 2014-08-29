#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/joystick.h>
#include <netinet/tcp.h>

char arduIp[15] = "192.168.1.109";
unsigned short int serverPort = 8080;

char msg;

int open_joystick(char *device_name) {
    int fd = -1;
    if (device_name == NULL) {
        return fd;
    }

    fd = open(device_name, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        printf("Could not locate joystick device %s\n", device_name);
        exit(1);
    }

    return fd;
}

void print_device_info(int fd) {
  int axes=0, buttons=0;
  char name[128];

  ioctl(fd, JSIOCGAXES, &axes);
  ioctl(fd, JSIOCGBUTTONS, &buttons);
  ioctl(fd, JSIOCGNAME(sizeof(name)), &name);

  printf("%s\n  %d Axes %d Buttons\n", name, axes, buttons);
}

void process_event(struct js_event jse) {
    if (jse.type == 2) {
        if (jse.number == 0) {
            if (jse.value < 0) {
    	        msg = 'S';
            } else if (jse.value > 0) {
	            msg = 'D';
            } else {
            	msg = 'H';
            }
        } else {
            if (jse.value < 0) {
	            msg = 'A';
            } else if (jse.value > 0) {
            	msg = 'I';
            } else {
                msg = 'H';
            }
        }
    }

    if (jse.type == 1 && jse.value > 0) {
        printf("%d\n", jse.number);
        //sprintf(msg, "%d\n", jse.number);
        //strcpy(msg, jse.number);
    }
}

int main() {
    int fd, i=0;
    struct js_event jse;

    fd = open_joystick("/dev/input/js1");
    print_device_info(fd);

    int listenfd,connfd;
    struct sockaddr_in servaddr,cliaddr;
    socklen_t clilen;

    listenfd=socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(serverPort);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd, 1024);

    clilen=sizeof(cliaddr);
    connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

    printf("GOT CONNECTION\n");
    int one = 1;

    setsockopt(connfd, SOL_TCP, TCP_NODELAY, &one, sizeof(one));
    while (1) {
        while (read(fd, &jse, sizeof(jse)) > 0) {
            process_event(jse);
            if(i>20){
                printf("Send message...");
                printf("%c\n",msg);
                if(sendto(connfd,&msg,1,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr)) < 0){
                    printf("Unable to send data to server");
	                exit(0);
                }
            }
            i++;

        }
    }

    return 0;
}

