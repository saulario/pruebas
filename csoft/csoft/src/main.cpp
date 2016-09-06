#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int, char **);
void signal_hanlder(int);

void signal_handler(int signo) {

    printf("Signal %d pulsada", signo);
    exit(signo);

}

int main(int argc, char **argv) {

    if (signal(SIGHUP, signal_handler) == SIG_ERR) {
        printf("Registrando SIGHUP\n");
        return EXIT_FAILURE;
    }
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        printf("Registrando SIGINT\n");
        return EXIT_FAILURE;
    }
/*
    if (signal(SIGKILL, signal_handler) == SIG_ERR) {
        printf("Registrando SIGKILL\n");
        return EXIT_FAILURE;
    }
*/
    if (signal(SIGTERM, signal_handler) == SIG_ERR) {
        printf("Registrando SIGTERM\n");
        return EXIT_FAILURE;
    }
    
    while(1) {
        sleep(1000);
    }
    








    return EXIT_SUCCESS;
}
