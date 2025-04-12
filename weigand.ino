// Wiegand signal emulation on Arduino
#define D0_PIN 2   // Wiegand Data 0 (D0)
#define D1_PIN 3   // Wiegand Data 1 (D1)

unsigned long siteCode = 1; // Facility code (16 bits)
unsigned long cardID = 10001; // Card ID (24 bits)

void setup() {
    pinMode(D0_PIN, OUTPUT);
    pinMode(D1_PIN, OUTPUT);
 
    // Start serial monitor for debugging
    Serial.begin(9600);

    // When no data is being sent, both DATA0 and DATA1 are pulled up to the "high" voltage level — usually +5 VDC
    // https://en.wikipedia.org/wiki/Wiegand_interface#cite_note-2
    digitalWrite(D0_PIN, HIGH);
    digitalWrite(D1_PIN, HIGH);
}

void loop() {
    sendWiegand26(siteCode, cardID);
    delay(5000);  // Wait for 5 seconds before repeating
}

/*
Wiegand Protocol:
- the most common is 26 bit format
- 1 bit leading parity bit (Even)
- 8 bits facility code
- 16 bits ID code
- 1 bit trailing parity bit (Odd)
*/
void sendWiegand26(unsigned long siteCode, unsigned long cardID) {
    // Combine facility code and card ID
    unsigned long long data = (siteCode << 24) | cardID;  // Shift site code to the left and add card ID

    // Calculate the parity bit using odd parity
    unsigned long long parity = calculateParity(data);

    // Add parity as the most significant bit (MSB)
    data = (data << 1) | parity;

    // Send the 26-bit Wiegand signal (start bit + site + card ID + parity)
    // When a 0 is sent the DATA0 wire is pulled to a low voltage while the DATA1 wire stays at a high voltage. 
    // When a 1 is sent the DATA1 wire is pulled to a low voltage while DATA0 stays at a high voltage
    for (int i = 25; i >= 0; i--) { 
    if ((data >> i) & 1) {
      digitalWrite(D0_PIN, HIGH);
      digitalWrite(D1_PIN, LOW);
    } else {
      digitalWrite(D0_PIN, LOW);
      digitalWrite(D1_PIN, HIGH);
    }
    delayMicroseconds(500); 
    digitalWrite(D0_PIN, HIGH);
    digitalWrite(D1_PIN, HIGH);
    }

    // Output for debugging
    Serial.print("Sent Facility Code: ");
    Serial.print(siteCode);
    Serial.print(", Card ID: ");
    Serial.println(cardID);
    printBinary(data, 26);
}

// Calculate the odd parity bit
unsigned long long calculateParity(unsigned long long data) {
    unsigned long long parity = 0;
    // Count the number of 1s in the data to calculate odd parity
    for (int i = 0; i < 40; i++) {
        parity ^= (data >> i) & 1;
    }
    return parity;
}

// Function to print binary representation of a number
void printBinary(unsigned long long data, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        // Print each bit from MSB to LSB
        Serial.print((int)((data >> i) & 1));
    }
    Serial.println();
}
