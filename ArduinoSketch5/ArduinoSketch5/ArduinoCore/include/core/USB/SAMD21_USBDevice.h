/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#pragma once

#include <Arduino.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "sync.h"

typedef uint8_t ep_t;

class USBDevice_SAMD21G18x {
public:
	USBDevice_SAMD21G18x() : usb(USB->DEVICE) {
		// Empty
	}

	// USB Device function mapping
	// ---------------------------

	// Reset USB Device
	inline void reset();

	// Enable
	inline void enable()  { usb.CTRLA.bit.ENABLE = 1; }
	inline void disable() { usb.CTRLA.bit.ENABLE = 0; }

	// USB mode (device/host)
	inline void setUSBDeviceMode() { usb.CTRLA.bit.MODE = USB_CTRLA_MODE_DEVICE_Val; }
	inline void setUSBHostMode()   { usb.CTRLA.bit.MODE = USB_CTRLA_MODE_HOST_Val;   }

	inline void runInStandby()   { usb.CTRLA.bit.RUNSTDBY = 1; }
	inline void noRunInStandby() { usb.CTRLA.bit.RUNSTDBY = 0; }
	inline void wakeupHost()     { usb.CTRLB.bit.UPRSM = 1; }

	// USB QoS
	inline void setDataSensitiveQoS() { usb.QOSCTRL.bit.DQOS = 2; }
	inline void setConfigSensitiveQoS() { usb.QOSCTRL.bit.CQOS = 2; }

	// USB speed
	inline void setFullSpeed()       { usb.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_FS_Val;   }
	inline void setLowSpeed()        { usb.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_LS_Val;   }
	inline void setHiSpeed()         { usb.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_HS_Val;   }
	inline void setHiSpeedTestMode() { usb.CTRLB.bit.SPDCONF = USB_DEVICE_CTRLB_SPDCONF_HSTM_Val; }

	// Authorize attach if Vbus is present
	inline void attach() { usb.CTRLB.bit.DETACH = 0; }
	inline void detach() { usb.CTRLB.bit.DETACH = 1; }

	// USB Interrupts
	inline bool isEndOfResetInterrupt()        { return usb.INTFLAG.bit.EORST; }
	inline void ackEndOfResetInterrupt()       { usb.INTFLAG.reg = USB_DEVICE_INTFLAG_EORST; }
	inline void enableEndOfResetInterrupt()    { usb.INTENSET.bit.EORST = 1; }
	inline void disableEndOfResetInterrupt()   { usb.INTENCLR.bit.EORST = 1; }

	inline bool isStartOfFrameInterrupt()      { return usb.INTFLAG.bit.SOF; }
	inline void ackStartOfFrameInterrupt()     { usb.INTFLAG.reg = USB_DEVICE_INTFLAG_SOF; }
	inline void enableStartOfFrameInterrupt()  { usb.INTENSET.bit.SOF = 1; }
	inline void disableStartOfFrameInterrupt() { usb.INTENCLR.bit.SOF = 1; }

	// USB Address
	inline void setAddress(uint32_t addr)   { usb.DADD.bit.DADD = addr; usb.DADD.bit.ADDEN = 1; }
	inline void unsetAddress()              { usb.DADD.bit.DADD = 0;    usb.DADD.bit.ADDEN = 0; }

	// Frame number
	inline uint16_t frameNumber() { return usb.FNUM.bit.FNUM; }

	// Load calibration values
	inline void calibrate();

	// USB Device Endpoints function mapping
	// -------------------------------------

	// Config
	inline void epBank0SetType(ep_t ep, uint8_t type) { usb.DeviceEndpoint[ep].EPCFG.bit.EPTYPE0 = type; }
	inline void epBank1SetType(ep_t ep, uint8_t type) { usb.DeviceEndpoint[ep].EPCFG.bit.EPTYPE1 = type; }

	// Interrupts
	inline uint16_t epInterruptSummary() { return usb.EPINTSMRY.reg; }

	inline bool epHasPendingInterrupts(ep_t ep)     { return usb.DeviceEndpoint[ep].EPINTFLAG.reg != 0; }
	inline bool epBank0IsSetupReceived(ep_t ep)     { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.RXSTP; }
	inline bool epBank0IsStalled(ep_t ep)           { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.STALL0; }
	inline bool epBank1IsStalled(ep_t ep)           { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.STALL1; }
	inline bool epBank0IsTransferFailed(ep_t ep)    { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.TRFAIL0; }
	inline bool epBank1IsTransferFailed(ep_t ep)    { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.TRFAIL1; }
	inline bool epBank0IsTransferComplete(ep_t ep)  { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.TRCPT0; }
	inline bool epBank1IsTransferComplete(ep_t ep)  { return usb.DeviceEndpoint[ep].EPINTFLAG.bit.TRCPT1; }

	inline void epAckPendingInterrupts(ep_t ep)     { usb.DeviceEndpoint[ep].EPINTFLAG.reg = 0x7F; }
	inline void epBank0AckSetupReceived(ep_t ep)    { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_RXSTP; }
	inline void epBank0AckStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL(1); }
	inline void epBank1AckStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL(2); }
	inline void epBank0AckTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRFAIL(1); }
	inline void epBank1AckTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRFAIL(2); }
	inline void epBank0AckTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT(1); }
	inline void epBank1AckTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT(2); }

	inline void epBank0EnableSetupReceived(ep_t ep)    { usb.DeviceEndpoint[ep].EPINTENSET.bit.RXSTP = 1; }
	inline void epBank0EnableStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTENSET.bit.STALL0 = 1; }
	inline void epBank1EnableStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTENSET.bit.STALL1 = 1; }
	inline void epBank0EnableTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTENSET.bit.TRFAIL0 = 1; }
	inline void epBank1EnableTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTENSET.bit.TRFAIL1 = 1; }
	inline void epBank0EnableTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTENSET.bit.TRCPT0 = 1; }
	inline void epBank1EnableTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTENSET.bit.TRCPT1 = 1; }

	inline void epBank0DisableSetupReceived(ep_t ep)    { usb.DeviceEndpoint[ep].EPINTENCLR.bit.RXSTP = 1; }
	inline void epBank0DisableStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTENCLR.bit.STALL0 = 1; }
	inline void epBank1DisableStalled(ep_t ep)          { usb.DeviceEndpoint[ep].EPINTENCLR.bit.STALL1 = 1; }
	inline void epBank0DisableTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTENCLR.bit.TRFAIL0 = 1; }
	inline void epBank1DisableTransferFailed(ep_t ep)   { usb.DeviceEndpoint[ep].EPINTENCLR.bit.TRFAIL1 = 1; }
	inline void epBank0DisableTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTENCLR.bit.TRCPT0 = 1; }
	inline void epBank1DisableTransferComplete(ep_t ep) { usb.DeviceEndpoint[ep].EPINTENCLR.bit.TRCPT1 = 1; }

	// Status
	inline bool epBank0IsReady(ep_t ep)    { return usb.DeviceEndpoint[ep].EPSTATUS.bit.BK0RDY; }
	inline bool epBank1IsReady(ep_t ep)    { return usb.DeviceEndpoint[ep].EPSTATUS.bit.BK1RDY; }
	inline void epBank0SetReady(ep_t ep)   { usb.DeviceEndpoint[ep].EPSTATUSSET.bit.BK0RDY = 1; }
	inline void epBank1SetReady(ep_t ep)   { usb.DeviceEndpoint[ep].EPSTATUSSET.bit.BK1RDY = 1; }
	inline void epBank0ResetReady(ep_t ep) { usb.DeviceEndpoint[ep].EPSTATUSCLR.bit.BK0RDY = 1; }
	inline void epBank1ResetReady(ep_t ep) { usb.DeviceEndpoint[ep].EPSTATUSCLR.bit.BK1RDY = 1; }

	inline void epBank0SetStallReq(ep_t ep)   { usb.DeviceEndpoint[ep].EPSTATUSSET.bit.STALLRQ0 = 1; }
	inline void epBank1SetStallReq(ep_t ep)   { usb.DeviceEndpoint[ep].EPSTATUSSET.bit.STALLRQ1 = 1; }
	inline void epBank0ResetStallReq(ep_t ep) { usb.DeviceEndpoint[ep].EPSTATUSCLR.bit.STALLRQ0 = 1; }
	inline void epBank1ResetStallReq(ep_t ep) { usb.DeviceEndpoint[ep].EPSTATUSCLR.bit.STALLRQ1 = 1; }

	// Packet
	inline uint16_t epBank0ByteCount(ep_t ep) { return EP[ep].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT; }
	inline uint16_t epBank1ByteCount(ep_t ep) { return EP[ep].DeviceDescBank[1].PCKSIZE.bit.BYTE_COUNT; }
	inline void epBank0SetByteCount(ep_t ep, uint16_t bc) { EP[ep].DeviceDescBank[0].PCKSIZE.bit.BYTE_COUNT = bc; }
	inline void epBank1SetByteCount(ep_t ep, uint16_t bc) { EP[ep].DeviceDescBank[1].PCKSIZE.bit.BYTE_COUNT = bc; }
	inline void epBank0SetMultiPacketSize(ep_t ep, uint16_t s) { EP[ep].DeviceDescBank[0].PCKSIZE.bit.MULTI_PACKET_SIZE = s; }
	inline void epBank1SetMultiPacketSize(ep_t ep, uint16_t s) { EP[ep].DeviceDescBank[1].PCKSIZE.bit.MULTI_PACKET_SIZE = s; }

	inline void epBank0SetAddress(ep_t ep, void *addr) { EP[ep].DeviceDescBank[0].ADDR.reg = (uint32_t)addr; }
	inline void epBank1SetAddress(ep_t ep, void *addr) { EP[ep].DeviceDescBank[1].ADDR.reg = (uint32_t)addr; }
	inline void epBank0SetSize(ep_t ep, uint16_t size) { EP[ep].DeviceDescBank[0].PCKSIZE.bit.SIZE = EP_PCKSIZE_SIZE(size); }
	inline void epBank1SetSize(ep_t ep, uint16_t size) { EP[ep].DeviceDescBank[1].PCKSIZE.bit.SIZE = EP_PCKSIZE_SIZE(size); }
	inline uint8_t EP_PCKSIZE_SIZE(uint16_t size) {
		switch (size) {
		case 8:    return 0;
		case 16:   return 1;
		case 32:   return 2;
		case 64:   return 3;
		case 128:  return 4;
		case 256:  return 5;
		case 512:  return 6;
		case 1023: return 7;
		default:   return 0;
		}
	}

	inline void epBank0DisableAutoZLP(ep_t ep) { EP[ep].DeviceDescBank[0].PCKSIZE.bit.AUTO_ZLP = 0; }
	inline void epBank1DisableAutoZLP(ep_t ep) { EP[ep].DeviceDescBank[1].PCKSIZE.bit.AUTO_ZLP = 0; }
	inline void epBank0EnableAutoZLP(ep_t ep)  { EP[ep].DeviceDescBank[0].PCKSIZE.bit.AUTO_ZLP = 1; }
	inline void epBank1EnableAutoZLP(ep_t ep)  { EP[ep].DeviceDescBank[1].PCKSIZE.bit.AUTO_ZLP = 1; }

	// USB Device Endpoint transactions helpers
	// ----------------------------------------

	inline void epReleaseOutBank0(ep_t ep, uint16_t s) {
		epBank0SetMultiPacketSize(ep, s);
		epBank0SetByteCount(ep, 0);
		epBank0ResetReady(ep);
	}

private:
	// USB Device registers
	UsbDevice &usb;

	// Endpoints descriptors table
	__attribute__((__aligned__(4)))	UsbDeviceDescriptor EP[USB_EPT_NUM];
};

void USBDevice_SAMD21G18x::reset() {
	usb.CTRLA.bit.SWRST = 1;
	memset(EP, 0, sizeof(EP));
	while (usb.SYNCBUSY.bit.SWRST) {}
	usb.DESCADD.reg = (uint32_t)(&EP);
}

void USBDevice_SAMD21G18x::calibrate() {
	// Load Pad Calibration data from non-volatile memory
	uint32_t *pad_transn_p = (uint32_t *) USB_FUSES_TRANSN_ADDR;
	uint32_t *pad_transp_p = (uint32_t *) USB_FUSES_TRANSP_ADDR;
	uint32_t *pad_trim_p   = (uint32_t *) USB_FUSES_TRIM_ADDR;

	uint32_t pad_transn = (*pad_transn_p & USB_FUSES_TRANSN_Msk) >> USB_FUSES_TRANSN_Pos;
	uint32_t pad_transp = (*pad_transp_p & USB_FUSES_TRANSP_Msk) >> USB_FUSES_TRANSP_Pos;
	uint32_t pad_trim   = (*pad_trim_p   & USB_FUSES_TRIM_Msk  ) >> USB_FUSES_TRIM_Pos;

	if (pad_transn == 0x1F)  // maximum value (31)
		pad_transn = 5;
	if (pad_transp == 0x1F)  // maximum value (31)
		pad_transp = 29;
	if (pad_trim == 0x7)     // maximum value (7)
		pad_trim = 3;

	usb.PADCAL.bit.TRANSN = pad_transn;
	usb.PADCAL.bit.TRANSP = pad_transp;
	usb.PADCAL.bit.TRIM   = pad_trim;
}

/*
 * USB EP generic handlers.
 */

class EPHandler {
public:
	virtual void handleEndpoint() = 0;
	virtual uint32_t recv(void *_data, uint32_t len) = 0;
	virtual uint32_t available() = 0;
	virtual int peek() = 0;
};

class DoubleBufferedEPOutHandler : public EPHandler {
public:
	enum { size = 64 };

	DoubleBufferedEPOutHandler(USBDevice_SAMD21G18x &usbDev, uint32_t endPoint) :
		usbd(usbDev),
		ep(endPoint),
		current(0), incoming(0),
		first0(0), last0(0), ready0(false),
		first1(0), last1(0), ready1(false),
		notify(false)
	{
		usbd.epBank0SetSize(ep, 64);
		usbd.epBank0SetType(ep, 3); // BULK OUT
		usbd.epBank0SetAddress(ep, const_cast<uint8_t *>(data0));
		usbd.epBank0EnableTransferComplete(ep);

		release();
	}

	virtual ~DoubleBufferedEPOutHandler() {
	}

	uint32_t _recv()
	{
		uint32_t i = 0;
		uint32_t len = 0;

		synchronized {
			len = _rx_buffer.availableForStore();
		}

		// R/W: current, first0/1, ready0/1, notify
		// R  : last0/1, data0/1
		if (current == 0) {
			synchronized {
				if (!ready0) {
					return 0;
				}
			}
			// when ready0==true the buffer is not being filled and last0 is constant
			for (; i<len && first0 < last0; i++) {
				_rx_buffer.store_char(data0[first0++]);
			}
			if (first0 == last0) {
				first0 = 0;
				current = 1;
				synchronized {
					ready0 = false;
					if (notify) {
						notify = false;
						release();
					}
				}
			}
		} else {
			synchronized {
				if (!ready1) {
					return 0;
				}
			}
			// when ready1==true the buffer is not being filled and last1 is constant
			for (; i<len && first1 < last1; i++) {
				_rx_buffer.store_char(data1[first1++]);
			}
			if (first1 == last1) {
				first1 = 0;
				current = 0;
				synchronized {
					ready1 = false;
					if (notify) {
						notify = false;
						release();
					}
				}
			}
		}
		return i;
	}

	virtual uint32_t recv(void *_data, uint32_t len) {
		_recv();
		uint32_t i = 0;
		uint8_t *data = reinterpret_cast<uint8_t *>(_data);
		synchronized {
			for (; i < len && _rx_buffer.available(); i++) {
				data[i] = _rx_buffer.read_char();
			}
		}
		return i;
	}

	virtual uint32_t _available() const {
		if (current == 0) {
			bool ready = ready0;
			synchronized {
				ready = ready0;
			}
			return ready ? (last0 - first0) : 0;
		} else {
			bool ready = false;
			synchronized {
				ready = ready1;
			}
			return ready ? (last1 - first1) : 0;
		}
	}

	virtual void handleEndpoint()
	{
		// R/W : incoming, ready0/1
		//   W : last0/1, notify
		if (usbd.epBank0IsTransferComplete(ep))
		{
			uint32_t received = usbd.epBank0ByteCount(ep);
			if (received == 0) {
				release();
			} else if (incoming == 0) {
			// Update counters and swap banks for non-ZLP's
				last0 = received;
				incoming = 1;
				usbd.epBank0SetAddress(ep, const_cast<uint8_t *>(data1));
				synchronized {
					ready0 = true;
					notify = ready1;
					if (!notify) {
						release();
					}
				}
			} else {
				last1 = received;
				incoming = 0;
				usbd.epBank0SetAddress(ep, const_cast<uint8_t *>(data0));
				synchronized {
					ready1 = true;
					notify = ready0;
					if (!notify) {
						release();
					}
				}
			}
			usbd.epAckPendingInterrupts(ep);
		}
	}

	// Returns how many bytes are stored in the buffers
	virtual uint32_t available() {
		_recv();
		return _rx_buffer.available();
	}

	virtual int peek() {
		_recv();
		return _rx_buffer.peek();
	}

	void release() {
		usbd.epReleaseOutBank0(ep, size);
	}

private:
	USBDevice_SAMD21G18x &usbd;

	arduino::RingBuffer _rx_buffer;

	const uint32_t ep;
	volatile uint32_t current, incoming;

	__attribute__((__aligned__(4)))	volatile uint8_t data0[size];
	uint32_t first0;
	volatile uint32_t last0;
	volatile bool ready0;

	__attribute__((__aligned__(4)))	volatile uint8_t data1[size];
	uint32_t first1;
	volatile uint32_t last1;
	volatile bool ready1;

	volatile bool notify;
};

