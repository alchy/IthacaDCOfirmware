# IthacaDCOfirmware

Digitally controlled oscillator (DCO) firmare for custom DCO board based on MSP chip

- receiving i2c commands (frequency/pitch)
- controls resistor ladder for voltage transistor exp. pair
- sends note on/off via IO for GAIN (ADSR)
- automate i2c addressing for easy DCO scaling (1 to 16 DCOs can be used in synth)
