package ch1

import (
	"fmt"
)

type Celsius float64
type Fahrenheit float64
type Kelvin float64

const (
	AbsoluteZeroc Celsius = -273.15
	FreezingC     Celsius = 0
	BoilingC      Celsius = 100
)

func (c Celsius) String() string {
	return fmt.Sprintf("%g ℃", c)
}

func (f Fahrenheit) String() string {
	return fmt.Sprintf("%g ℉", f)
}

func CToF(c Celsius) Fahrenheit {
	return Fahrenheit((c * 9 / 5) + 32)
}

func FToC(f Fahrenheit) Celsius {
	return Celsius((f - 32) * 5 / 9)
}

func KtoC(k Kelvin) Celsius {
	return Celsius(k - 273.15)
}

func CtoK(c Celsius) Kelvin {
	return Kelvin(c + 273.15)
}
