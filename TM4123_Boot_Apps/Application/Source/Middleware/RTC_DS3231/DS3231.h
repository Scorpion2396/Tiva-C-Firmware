#ifndef DS3231_H
#define DS3231_H

#define DS3231_SLAVE_ADD    0x68
#define DS3231_SEC_ADD      0x00
#define DS3231_MIN_ADD      0x01
#define DS3231_HRS_ADD      0x02

int ds3231_read_sec();
void ds3231_write_sec(int sec_value);

int ds3231_read_min();
void ds3231_write_min(int min_value);

int ds3231_read_hrs();
void ds3231_write_hrs(int hrs_value);

static int process_get_data(int value);
static int process_set_data(int value);

#endif


