#include <iostream>
#include <fcntl.h>
#include "Rendering/libs/libevdev/libevdev.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

    struct libevdev *dev = nullptr;
    int fd;
    int rc = 1;
    std::string path = "/dev/input/event3";
    fd = open(path.c_str(), O_RDONLY);
    std::cout<<"FUCK ME BACKWARDS"<<fd;
    rc = libevdev_new_from_fd(fd, &dev);
    std::cout<<"FUCK ME SIDEWARDS"<<rc;
    if (rc < 0) {
        fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
        exit(1);
    }
    printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
    printf("Input device ID: bus %#x vendor %#x product %#x\n",
           libevdev_get_id_bustype(dev),
           libevdev_get_id_vendor(dev),
           libevdev_get_id_product(dev));
    if (!libevdev_has_event_type(dev, EV_REL) ||
        !libevdev_has_event_code(dev, EV_KEY, BTN_LEFT)) {
        printf("This device does not look like a mouse\n");
        exit(1);
        }
    do {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
        /*if (rc == 0)
            printf("Event: %s %s %d\n",
                   libevdev_get_event_type_name(ev.type),
                   libevdev_get_event_code_name(ev.type, ev.code),
                   ev.value);
        */
    } while (rc == 1 || rc == 0 || rc == -EAGAIN);
    return 0;
}
