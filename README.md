# Arduino Capacitance Measurement Using RC Time Constant

This project explains how to measure an unknown capacitor using an Arduino by converting capacitance into time using the RC charging principle.

It is intended for academic laboratories, mini projects, and viva examinations.

---

## 1. Motivation

Arduino does not have a native way to measure capacitance directly.  
However, it can measure time with high precision.

By exploiting the predictable charging behavior of an RC circuit, capacitance can be calculated accurately from the measured charging time.

---

## 2. Theory of Operation

The operation of this project is based on the **RC time constant principle**.

When a capacitor is charged through a resistor, the voltage across the capacitor does not rise instantly. Instead, it increases exponentially with time. The rate of charging depends on the product of the resistance (R) and capacitance (C), known as the **time constant**.

The time constant is defined as:

τ = R × C

At a time equal to one time constant (t = τ), the voltage across the capacitor reaches approximately **63.2% of the supply voltage**.

By measuring the time taken for the capacitor voltage to reach this 63% level using the Arduino’s ADC and knowing the resistor value, the capacitance can be calculated as:

C = t / R


---

## 3. Time Constant

The time constant of an RC circuit is defined as:

τ = R × C

At time t = τ, the capacitor voltage reaches approximately 63.2% of the supply voltage.

This fixed characteristic allows capacitance to be determined without complex calculations.

---

## 4. Formula Used

By measuring the time taken for the capacitor voltage to reach 63% of Vcc, capacitance is calculated as:

C = t / R

---

## 5. Hardware Requirements

- Arduino Uno / Nano / Mega
- One resistor (recommended range: 10 kΩ to 100 kΩ)
- Unknown capacitor
- Breadboard
- Jumper wires

---

## 6. Circuit Diagram
<img width="716" height="613" alt="new" src="https://github.com/user-attachments/assets/89ae690a-211b-4196-a120-2ae2ec02dc3e" />
<img width="1042" height="450" alt="new schematic" src="https://github.com/user-attachments/assets/bbff2a9b-7938-4b82-841d-859fed9cac34" />


## 7. Circuit Connection


Important notes:
- The ADC pin must be connected directly to the capacitor node
- The ADC should not be placed before the resistor
- For electrolytic capacitors, ensure correct polarity

---

## 8. Algorithm

1. Discharge the capacitor by setting the charging pin LOW  
2. Set the charging pin HIGH to begin charging  
3. Start timing using `micros()`  
4. Continuously monitor the ADC value  
5. Stop timing when the voltage reaches 63% of Vcc  
6. Calculate capacitance using C = t / R  
7. Display the result on the Serial Monitor  

---
