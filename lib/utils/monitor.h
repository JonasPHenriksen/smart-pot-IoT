#pragma once
void monitor_init(int baudrate);
void monitor_send(char *data);
char* monitor_receive();