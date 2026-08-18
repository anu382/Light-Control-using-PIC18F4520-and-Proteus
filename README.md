
# 💡 Automatic Light Control System (PIC18F4520 + LDR)

## 📖 Overview
This project demonstrates an **Automatic Light Control System** using a **PIC18F4520 microcontroller** and an **LDR (Light Dependent Resistor)**.  
The system automatically turns a light ON or OFF depending on the surrounding light intensity, helping save energy and enabling smart lighting.

---

## 🚀 Features
- Automatic light detection  
- Relay-based AC load control  
- Real-time status display on 16x2 LCD  
- Energy-efficient design  
- Simple and low-cost implementation  

---

## 🧰 Components Used
- PIC18F4520 Microcontroller  
- LDR (Light Dependent Resistor)  
- BC337 Transistor  
- 12V Relay  
- Diode (1N4007)  
- 16x2 LCD (LM016L)  
- Resistors (10kΩ, 2kΩ, etc.)  
- Power Supply  

---

## ⚙️ How It Works
1. The **LDR** senses ambient light intensity.  
2. Its resistance changes with light, creating a variable voltage.  
3. The **PIC18F4520** reads this voltage using its ADC.  
4. The value is compared with a predefined threshold.  
5. Based on the result:  
   - 🌙 **Dark → Relay ON → Light ON**  
   - ☀️ **Bright → Relay OFF → Light OFF**  
6. The **LCD** displays the system status.

---

## 🔌 Circuit Description
- LDR is connected in a **voltage divider** configuration.  
- Analog output is fed to the **ADC pin** of the microcontroller.  
- A **BC337 transistor** drives the relay.  
- A **flyback diode (1N4007)** protects against voltage spikes.  
- LCD displays light intensity or ON/OFF status.

---

## 💡 Applications
- Automatic street lighting  
- Home automation systems  
- Garden lighting  
- Industrial lighting control  

---

## 🔧 Future Improvements
- Adjustable threshold using potentiometer  
- Add IoT connectivity (WiFi/Bluetooth)  
- Mobile app control  
- PWM-based dimming system  

---


## 👨‍💻 Author
Anushka Bakare 

```




