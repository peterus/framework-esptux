#ifndef SPI_CHIP_H_
#define SPI_CHIP_H_

#include "HardwareSPI.h"
#include "Utility.h"

class SPIChip {
public:
  /**
   * Do a SPI transaction to the selected device
   *
   * @param outBuf if NULL it will be not used (zeros will be sent)
   * @param inBuf if NULL it will not be used (device response bytes will be discarded)
   * @param deassertCS after last transaction (if not set, it will be left asserted)
   * @return 0 for success, else ERRNO fault code
   */
  virtual int transfer(const uint8_t *outBuf, uint8_t *inBuf, size_t bufLen, bool deassertCS = true) = 0;

  /// is this chip controlling real hardware?
  virtual bool isSimulated() {
    return false;
  }

  virtual ~SPIChip() {
  }
};

class SimSPIChip : public SPIChip {
public:
  /**
   * Do a SPI transaction to the selected device
   *
   * @param outBuf if NULL it will be not used (zeros will be sent)
   * @param inBuf if NULL it will not be used (device response bytes will be discarded)
   * @param deassertCS after last transaction (if not set, it will be left asserted)
   * @return 0 for success, else ERRNO fault code
   */
  int transfer(const uint8_t *outBuf, uint8_t *inBuf, size_t bufLen, bool deassertCS = true) {
    UNUSED(outBuf);
    UNUSED(inBuf);
    UNUSED(bufLen);
    UNUSED(deassertCS);
    // log(SysSPI, LogVerbose, "SIM: spiTransfer(%d) -> %d", bufLen);
    return 0;
  }

  /// is this chip controlling real hardware?
  virtual bool isSimulated() {
    return true;
  }

  virtual ~SimSPIChip() {
  }
};

// FIXME, this is kinda skanky, but for now we assume one SPI device
extern SPIChip *spiChip;

#endif