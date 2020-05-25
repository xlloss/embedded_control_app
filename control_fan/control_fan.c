#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVF "/sys/class/pwm/pwmchip"
#define DEVF_EXPORT "export"
#define DEVF_UNEXPORT "unexport"
#define DEVF_PWM_ENABLE "enable"
#define DEVF_PWM_PERIOD "period"
#define DEVF_PWM_DUTY "duty_cycle"

struct sys_pwm {
	int port;
	int channel;
	int enable;
	char *con_buf;
};

int pwm_chan_export(struct sys_pwm *pwm)
{
    int fd;
    char writebuf[5];
    int w_len;
    int pwm_channel, pwm_port;
    char *conbuf;

    conbuf = pwm->con_buf;
    pwm_channel = pwm->channel;
    pwm_port = pwm->port;
    sprintf(conbuf, "%s/%d/%d/%s", DEVF,
        pwm_port, pwm_channel, DEVF_EXPORT);

    fd = open(conbuf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "0");
    w_len = write(fd, writebuf, 1);
    if (w_len < 0)
        perror("write");

    close(fd);
}

int pwm_chan_unexport(struct sys_pwm *pwm)
{
    int fd;
    char writebuf[5];
    int w_len;
    int pwm_channel, pwm_port;
    char *conbuf;

    conbuf = pwm->con_buf;
    pwm_channel = pwm->channel;
    pwm_port = pwm->port;
    sprintf(conbuf, "%s/%d/%d/%s", DEVF,
        pwm_port, pwm_channel, DEVF_UNEXPORT);

    fd = open(conbuf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "0");
    w_len = write(fd, writebuf, 1);
    if (w_len < 0)
        perror("write");

    close(fd);
}

int pwm_set_duty(struct sys_pwm *pwm, int duty_time)
{
    int fd;
    char writebuf[20];
    int w_len;
    int pwm_channel, pwm_port;
    char *conbuf;

    conbuf = pwm->con_buf;
    pwm_channel = pwm->channel;
    pwm_port = pwm->port;
    sprintf(conbuf, "%s/%d/%d/%s", DEVF,
        pwm_port, pwm_channel, DEVF_PWM_DUTY);

    fd = open(conbuf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "%d", duty_time);
    w_len = write(fd, writebuf, strlen(writebuf));
    if (w_len < 0)
        perror("write");

    close(fd);
}

int pwm_set_period(struct sys_pwm *pwm, int period_time)
{
    int fd;
    char writebuf[20];
    int w_len;
    int pwm_channel, pwm_port;
    char *conbuf;

    conbuf = pwm->con_buf;
    pwm_channel = pwm->channel;
    pwm_port = pwm->port;
    sprintf(conbuf, "%s/%d/%d/%s", DEVF,
        pwm_port, pwm_channel, DEVF_PWM_PERIOD);

    fd = open(conbuf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "%d", period_time);
    w_len = write(fd, writebuf, strlen(writebuf));
    if (w_len < 0)
        perror("write");

    close(fd);
}

int pwm_set_enable(struct sys_pwm *pwm)
{
    int fd;
    char writebuf[20];
    int w_len;
    int pwm_channel, pwm_port, enable;
    char *conbuf;

    conbuf = pwm->con_buf;
    pwm_channel = pwm->channel;
    pwm_port = pwm->port;

    sprintf(conbuf, "%s/%d/%d/%s", DEVF,
        pwm_port, pwm_channel, DEVF_PWM_ENABLE);

    fd = open(conbuf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    enable = pwm->enable;
    sprintf(writebuf, "%d", enable);
    w_len = write(fd, writebuf, strlen(writebuf));
    if (w_len < 0)
        perror("write");

    close(fd);
}


int main(int argc, char** argv)
{
    int fd;
    int port, duty, channel, period;
    int opts;
    int option_index = 0;
    char *pwm_ch = "0\r\n";
    char readbuf[10];
    char writebuf[10];
    char conbuf[50];
    int w_len;
    int i;

    /* getopt_long stores the option index here. */
    struct option long_options[] = {
        {"period", required_argument, 0, 'p'},
        {"duty", required_argument, 0, 'd'},
        {"port", required_argument, 0, 'o'},
        {"channel", required_argument, 0, 'c'},
        {"?",  no_argument, 0, '?'},
        {0, 0, 0, 0}
    };

    while (1) {
        opts = getopt_long (argc, argv,
        "p:d:o:c:", long_options, &option_index);

        /* Detect the end of the options. */
        if (opts == -1)
            break;

        switch (opts) {
        case 'p':
            period = atoi(optarg);
            break;

        case 'd':
            duty = atoi(optarg);
            break;

        case 'o':
            port = atoi(optarg);
            break;

        case 'c':
            channel = atoi(optarg);
            break;
        case '?':
            printf("help");
            break;
        default:
                break;
        }
    }

    return 0;
}
