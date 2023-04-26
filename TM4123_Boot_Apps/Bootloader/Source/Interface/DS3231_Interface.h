#ifndef DS3231_H
#define DS3231_H

extern int ds3231_read_sec();
extern void ds3231_write_sec(int sec_value);

extern int ds3231_read_min();
extern void ds3231_write_min(int min_value);

extern int ds3231_read_hrs();
extern void ds3231_write_hrs(int hrs_value);

#endif
