/********************************** (C) COPYRIGHT *******************************
* File Name          : usb_desc.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/07/15
* Description        : USB Descriptors.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"
#include "usb_desc.h"

/* USB Device Descriptors */
const uint8_t  USBD_DeviceDescriptor[] = { 
    USBD_SIZE_DEVICE_DESC,           // bLength
    0x01,                            // bDescriptorType (Device)
    0x00,0x02,//0x10, 0x01,                      // bcdUSB 1.10
    0x00,                            // bDeviceClass (Use class information in the Interface Descriptors)
    0x00,                            // bDeviceSubClass 
    0x00,                            // bDeviceProtocol 
    DEF_USBD_UEP0_SIZE,              // bMaxPacketSize0 8
    0x0D, 0x0F,                      // idVendor 0x0F0D Hori Co., Ltd
    0x92, 0x00,                      // idProduct 0x0092
    0x00, 0x01,                      // bcdDevice 2.00
    0x01,                            // iManufacturer (String Index)
    0x02,                            // iProduct (String Index)
    0x00,                            // iSerialNumber (String Index)
    0x01,                            // bNumConfigurations 1
};

/* USB Configration Descriptors */
const uint8_t  USBD_ConfigDescriptor[] = { 
    /* Configuration Descriptor */
    0x09,                           // bLength
    0x02,                           // bDescriptorType
    USBD_SIZE_CONFIG_DESC & 0xFF, USBD_SIZE_CONFIG_DESC >> 8, // wTotalLength
    0x01,                           // bNumInterfaces
    0x01,                           // bConfigurationValue
    0x03,//0x03                           // iConfiguration (String Index)
    0xA0,//0x80,                           // bmAttributes Remote Wakeup
    0xFA,//0x46,                           // bMaxPower 70mA

    /* Interface Descriptor */
    0x09,                           // bLength
    0x04,                           // bDescriptorType (Interface)
    0x00,                           // bInterfaceNumber 0
    0x00,                           // bAlternateSetting
    0x02,                           // bNumEndpoints 2
    0x03,                           // bInterfaceClass
    0x00,                           // bInterfaceSubClass
    0x00,                           // bInterfaceProtocol
    0x00,                           // iInterface (String Index)

    /* HID Descriptor */
    0x09,                           // bLength
    0x21,                           // bDescriptorType
    0x11, 0x01,                     // bcdHID
    0x00,                           // bCountryCode
    0x01,                           // bNumDescriptors
    0x22,                           // bDescriptorType
    USBD_SIZE_REPORT_DESC & 0xFF, USBD_SIZE_REPORT_DESC >> 8, // wDescriptorLength

    /* Endpoint Descriptor */
    0x07,                           // bLength
    0x05,                           // bDescriptorType
    0x02,//0x01,                           // bEndpointAddress: OUT Endpoint 1 // out 2
    0x03,                           // bmAttributes
    0x40, 0x00,                     // wMaxPacketSize
    0x01,                           // bInterval: 1mS
    
    /* Endpoint Descriptor */
    0x07,                           // bLength
    0x05,                           // bDescriptorType
    0x81,//0x82,                           // bEndpointAddress: IN Endpoint 2 // in 1
    0x03,                           // bmAttributes
    0x40, 0x00,                     // wMaxPacketSize
    0x01,                           // bInterval: 1mS
};

/* USB String Descriptors */
const uint8_t USBD_StringLangID[USBD_SIZE_STRING_LANGID] = {
	USBD_SIZE_STRING_LANGID,
	USB_STRING_DESCRIPTOR_TYPE,
	0x09,
	0x04 
};

/* USB Device String Vendor */
const uint8_t USBD_StringVendor[USBD_SIZE_STRING_VENDOR] = {
	USBD_SIZE_STRING_VENDOR,    
	USB_STRING_DESCRIPTOR_TYPE,           
	'E',0,'a',0,'s',0,'y',0,'c',0,'o',0,'n',0
};

/* USB Device String Product */
const uint8_t USBD_StringProduct[USBD_SIZE_STRING_PRODUCT] = {
	USBD_SIZE_STRING_PRODUCT,         
	USB_STRING_DESCRIPTOR_TYPE,        
    'E',0,'a',0,'s',0,'y',0,'c',0,'o',0,'n',0,
	  ' ',0,'P',0,'r',0,'o',0,' ',0,
	  'C',0,'o',0,'n',0,'t',0,'r',0,'o',0,'l',0,'l',0,'e',0,'r',0,
};

/* USB Device String Serial */
uint8_t USBD_StringSerial[USBD_SIZE_STRING_SERIAL] = {
	USBD_SIZE_STRING_SERIAL,          
	USB_STRING_DESCRIPTOR_TYPE,                   
	'0', 0, '1', 0, '2', 0, '3', 0, '4', 0, '5', 0 , '6', 0, '7', 0, '8', 0, '9', 0
};

/* HID Report Descriptor */
const uint8_t USBD_HidRepDesc[USBD_SIZE_REPORT_DESC] =
{
  /* USER CODE BEGIN 0 */
  0x05, 0x01,               //Usage Page (Generic Desktop)
  0x09, 0x05,               //Usage (Game Pad)
  0xA1, 0x01,               //Collection (Application)
  0x15, 0x00,               //    Logical Minimum (0)
  0x25, 0x01,               //    Logical Maximum (1)
  0x35, 0x00,               //    Physical Minimum (0)
  0x45, 0x01,               //    Physical Maximum (1)
  0x75, 0x01,               //    Report Size (1)
  0x95, 0x10,               //    Report Count (16)
  0x05, 0x09,               //    Usage Page (Button)
  0x19, 0x01,               //    Usage Minimum (Button 1)
  0x29, 0x10,               //    Usage Maximum (Button 16)
  0x81, 0x02,               //    Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
  0x05, 0x01,               //    Usage Page (Generic Desktop)
  0x25, 0x07,               //    Logical Maximum (7)
  0x46, 0x3B, 0x01,         //    Physical Maximum (315)
  0x75, 0x04,               //    Report Size (4)
  0x95, 0x01,               //    Report Count (1)
  0x65, 0x14,               //    Unit (Eng Rot: Degree)
  0x09, 0x39,               //    Usage (Hat Switch)
  0x81, 0x42,               //    Input (Data,Var,Abs,NWrp,Lin,Pref,Null,Bit)
  0x65, 0x00,               //    Unit (None)
  0x95, 0x01,               //    Report Count (1)
  0x81, 0x01,               //    Input (Cnst,Ary,Abs)
  0x26, 0xFF, 0x00,         //    Logical Maximum (255)
  0x46, 0xFF, 0x00,         //    Physical Maximum (255)
  0x09, 0x30,               //    Usage (X)
  0x09, 0x31,               //    Usage (Y)
  0x09, 0x32,               //    Usage (Z)
  0x09, 0x35,               //    Usage (Rz)
  0x75, 0x08,               //    Report Size (8)
  0x95, 0x04,               //    Report Count (4)
  0x81, 0x02,               //    Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
  0x06, 0x00, 0xFF,         //    Usage Page (Vendor-Defined 1)
  0x09, 0x20,               //    Usage (Vendor-Defined 32)
  0x95, 0x01,               //    Report Count (1)
  0x81, 0x02,               //    Input (Data,Var,Abs,NWrp,Lin,Pref,NNul,Bit)
  0x0A, 0x21, 0x26,         //    Usage (Vendor-Defined 9761)
  0x95, 0x08,               //    Report Count (8)
  0x91, 0x02,               //    Output (Data,Var,Abs,NWrp,Lin,Pref,NNul,NVol,Bit)
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};




