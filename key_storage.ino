#include "USB.h"
#include "USBMSC.h"
#include "FS.h"
#include "FFat.h"
#include "WiFi.h"
#include "esp_bt.h"  

USBMSC MSC;

#define DISK_SIZE (100 * 1024) 

typedef int32_t i32;
typedef uint32_t u32;
typedef uint8_t u8;


u8 msc_disk[DISK_SIZE];

i32 onRead(u32 lba, u32 offset, void* buffer, u32 bufsize) {
    u8* dst = (u8*)buffer;
    memcpy(dst, msc_disk + offset, bufsize);
    return bufsize;
}

i32 onWrite(u32 lba, u32 offset, u8* buffer, u32 bufsize) {
    memcpy(msc_disk + offset, buffer, bufsize);
    return bufsize;
}

void setup() {
    Serial.begin(115200);

    WiFi.mode(WIFI_OFF);
    btStop(); 

    MSC.vendorID("XIAO");
    MSC.productID("USB Drive");
    MSC.onRead(onRead);
    MSC.onWrite(onWrite);
    MSC.mediaPresent(true);
    MSC.begin(DISK_SIZE/512, 512);
    
    USB.begin();
}

void loop() {
    delay(1000);
}