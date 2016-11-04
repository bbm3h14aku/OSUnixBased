OUTPUT_FORMAT("binary")
ENTRY(RealMode)
phys = 0x00008000;
SECTIONS
{
	.text phys	: {
		*(.text)
	}
	.data	: {
		*(.data)
	}
	.bss	: {
		*(.bss)
	}
}