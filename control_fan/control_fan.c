#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>

#define DEVFILE "/sys/class/pwm/pwmchip1/"
#define DEVFILE_EXPORT "export"
#define DEVFILE_UNEXPORT "unexport"
#define DEVFILE_PWM0 "pwm0"
#define DEVFILE_PWM0_ENABLE "enable"
#define DEVFILE_PWM0_PERIOD "period"
#define DEVFILE_PWM0_DUTY "duty_cycle"

//#define DEVFILE "/sys/class/pwm/pwmchip1/npwm"

int pwm_chan_export(char *control_buf)
{
    int fd;
    char writebuf[5];
    int w_len;

    sprintf(control_buf, "%s%s%s", DEVFILE, DEVFILE_PWM0, DEVFILE_PWM0_DUTY);
    fd = open(control_buf, O_WRONLY);
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

int pwm_chan_unexport(char *control_buf)
{
    int fd;
    char writebuf[5];
    int w_len;

    sprintf(control_buf, "%s%s%s", DEVFILE, DEVFILE_PWM0, DEVFILE_UNEXPORT);
    fd = open(control_buf, O_WRONLY);
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

int pwm_set_duty(char *control_buf, int duty_time)
{
    int fd;
    char writebuf[20];
    int w_len;

    sprintf(control_buf, "%s%s", DEVFILE, DEVFILE_PWM0_DUTY);
    fd = open(control_buf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "%s", duty_time);
    w_len = write(fd, writebuf, strlen(writebuf));
    if (w_len < 0)
        perror("write");

    close(fd);
}

int pwm_set_period(char *control_buf, int period_time)
{
    int fd;
    char writebuf[20];
    int w_len;

    sprintf(control_buf, "%s%s", DEVFILE, DEVFILE_PWM0_PERIOD);
    fd = open(control_buf, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 0;
    }

    sprintf(writebuf, "%s", duty_time);
    w_len = write(fd, writebuf, strlen(writebuf));
    if (w_len < 0)
        perror("write");

    close(fd);
}

int main(int argc, char** argv)
{
    int fd;
    int led, value;
    int opts;
    int option_index = 0;
    char *pwm_ch = "0\r\n";
    char readbuf[10];
    char writebuf[10];
    char conbuf[50];
    int w_len;
    int i;
//    /* getopt_long stores the option index here. */
//    struct option long_options[] = {
//        {"led", required_argument, 0, 'l'},
//        {"value", required_argument, 0, 'v'},
//        {"?",  no_argument, 0, '?'},
//        {0, 0, 0, 0}
//    };
//
//    while (1) {
//        opts = getopt_long (argc, argv,
//        "l:v:", long_options, &option_index);
//
//        /* Detect the end of the options. */
//        if (opts == -1)
//            break;
//
//        switch (opts) {
//        case 'l':
//            led = atoi(optarg);
//            break;
//
//        case 'v':
//            value = atoi(optarg);
//            break;
//
//        case '?':
//            printf(
//                "./test_led_char_driver -l LED_NUM -v ON/OFF\r\n"
//                "LED_NUM : 0 - 3\r\n"
//                "ON/OFF :\r\n"
//                "   ON : 1\r\n"
//                "   OFF: 0\r\n"
//                "./test_led_char_driver -l 0 -v 1\r\n : led 0 on\r\n"
//                "./test_led_char_driver -l 0 -v 0\r\n : led 0 off\r\n");
//            break;
//        default:
//                break;
//        }
//    }

    return 0;
}
