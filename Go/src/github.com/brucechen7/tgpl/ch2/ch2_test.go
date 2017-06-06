package ch2

import "testing"
import "math"

func isEqual(f1, f2 float64) bool {
	return math.Dim(f1, f2) < 0.00001
}
func TestCToOther(t *testing.T) {
	var c Celsius = 1.0
	if f := CToF(c); !isEqual(float64(f), 33.800) {
		t.Errorf("0 ℃ must be %f ℉", f)
	}
	if k := CtoK(c); !isEqual(float64(k), 274.15) {
		t.Errorf("0 ℃ must be %f ", k)
	}
}

func TestKToC(t *testing.T) {
	var k Kelvin = 1.0

	if c := KtoC(k); !isEqual(float64(c), 272.15) {
		t.Errorf("1 K must be %f ℃", c)
	}
}

func TestFToC(t *testing.T) {
	var f Fahrenheit = 1.0
	if c := FToC(f); !isEqual(float64(c), -17.222) {
		t.Errorf("1 ℉ must be %f ℃", c)
	}

}
