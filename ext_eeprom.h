
extern void scl_out (unsigned char port, unsigned char value);

extern void sda_out (unsigned char port, unsigned char value);

extern void start_i2c (unsigned char port);

extern void stop_i2c (unsigned char port);

extern unsigned char wr_i2c(unsigned char port, unsigned char value);

extern unsigned char rd_i2c(unsigned char port, unsigned char ack);

extern void write_i2c_device(unsigned int address, unsigned char value);

extern unsigned char read_i2c_device(unsigned int address);

extern void halfclockdelay(void);

extern void pinit (void);
