// license:BSD-3-Clause
// copyright-holders:R. Belmont
/*********************************************************************

    timemasterho.h

    Implemention of the Applied Engineering TimeMaster H.O.

*********************************************************************/

#ifndef __A2BUS_TIMEMASTERHO__
#define __A2BUS_TIMEMASTERHO__

#include "a2bus.h"
#include "machine/6821pia.h"
#include "machine/msm5832.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

class a2bus_timemasterho_device:
	public device_t,
	public device_a2bus_card_interface
{
public:
	// construction/destruction
	a2bus_timemasterho_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, uint32_t clock, const char *shortname, const char *source);
	a2bus_timemasterho_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const override;
	virtual const tiny_rom_entry *device_rom_region() const override;
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_WRITE8_MEMBER(pia_out_a);
	DECLARE_WRITE8_MEMBER(pia_out_b);
	DECLARE_WRITE_LINE_MEMBER(pia_irqa_w);
	DECLARE_WRITE_LINE_MEMBER(pia_irqb_w);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

	// overrides of standard a2bus slot functions
	virtual uint8_t read_c0nx(address_space &space, uint8_t offset) override;
	virtual void write_c0nx(address_space &space, uint8_t offset, uint8_t data) override;
	virtual uint8_t read_cnxx(address_space &space, uint8_t offset) override;
	virtual uint8_t read_c800(address_space &space, uint16_t offset) override;

	required_device<pia6821_device> m_pia;
	required_device<msm5832_device> m_msm5832;
	required_ioport m_dsw1;

private:
	void update_irqs();

	uint8_t *m_rom;
	bool m_irqa, m_irqb;
	bool m_started;
};

// device type definition
extern const device_type A2BUS_TIMEMASTERHO;

#endif /* __A2BUS_TIMEMASTERHO__ */
