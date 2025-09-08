## aug 13 LAb - 32 bit

Alright, let’s go step-by-step and break down these **three programs** like I’m explaining to a 7-year-old.

---

## **Program 1 – Adding Two Large Numbers**

(First image)

### Purpose:

This program adds two big numbers (each number is stored in two parts because registers can only hold small pieces at a time).

### Step-by-step:

```
DATA SEGMENT
NUM1 DW 1234H,5678H
NUM2 DW 0AB12H,0CDEFH
RESULT DW 3 DUP(?)
```

* **DATA SEGMENT** → We are telling the computer, “Here is the storage box for our numbers.”
* **NUM1** → First big number: first half = `1234H`, second half = `5678H`.
* **NUM2** → Second big number: first half = `AB12H`, second half = `CDEFH`.
* **RESULT** → A box to store the answer. `3 DUP(?)` means make 3 empty spots.

---

```
CODE SEGMENT
ASSUME CS:CODE, DS:DATA
```

* We say: **CS** (Code Segment) will use `CODE` and **DS** (Data Segment) will use `DATA`.

---

```
MOV AX,DATA
MOV DS,AX
```

* Put the **address of DATA** into DS (so DS can find our numbers).

```
MOV DX,00H
```

* DX will store carry from addition. Start with `0`.

---

```
MOV AX,NUM1
MOV BX,NUM2
CLC
ADD AX,BX
MOV RESULT,AX
```

* Load **first halves** of numbers into AX and BX.
* **CLC** means "clear carry".
* Add them → store in RESULT.

---

```
MOV AX,NUM1+2
MOV BX,NUM2+2
ADC AX,BX
MOV RESULT+2,AX
```

* Load **second halves** of numbers.
* **ADC** = Add with Carry (if the first addition had overflow).
* Store result in RESULT+2 (next part of memory).

---

```
ADDC DX,00H
MOV RESULT+4,DX
```

* Save final carry into RESULT+4.

---

```
MOV AH,4CH
INT 21H
```

* End program and return to DOS.

📌 **Summary**: It adds two big numbers (4 bytes each) and stores result in 6 bytes.

---

## **Program 2 – Subtracting Two Large Numbers**

(Second image)

This one is just like Program 1 but instead of **ADD** it uses **SUB**.

---

```
DATA SEGMENT
NUM2 DW 1234H,5678H
NUM1 DW 0AB12H,0CDEFH
RESULT DW 3 DUP(?)
```

* NUM2 is the first number, NUM1 is the second.
* We will do NUM2 - NUM1.

---

```
MOV AX,NUM1
MOV BX,NUM2
CLC
SUB AX,BX
MOV RESULT,AX
```

* First halves → Subtract BX from AX → store.

---

```
MOV AX,NUM1+2
MOV BX,NUM2+2
SBB AX,BX
MOV RESULT+2,AX
```

* Second halves → Subtract with borrow (SBB).

---

```
SBB DX,00H
MOV RESULT+4,DX
```

* Store final borrow into last part.

📌 **Summary**: It subtracts two large numbers using SUB and SBB.




NNNNNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN





## **Program 3 – Printing Two Messages**

(Third image)

This one is simpler — it just prints two words.

---

```
DATA SEGMENT
MSG1 DB "HELLO$"
MSG2 DB "WORLD$"
DATA ENDS
```

* MSG1 = "HELLO\$"
* MSG2 = "WORLD\$"
* `$` means “end of text” for DOS.

---

```
MOV AX,DATA
MOV DS,AX
```

* Load the address of DATA into DS.

---

```
LEA DX,MSG1
MOV AH,09H
INT 21H
```

* **LEA DX,MSG1** → Put the starting address of MSG1 into DX.
* AH = 09H means “print string”.
* INT 21H calls DOS to print "HELLO".

---

```
LEA DX,MSG2
MOV AH,09H
INT 21H
```

* Same thing for "WORLD".

---

```
MOV AH,4CH
INT 21H
```

* End the program.

📌 **Summary**: Prints “HELLO” and “WORLD” one after another.

---

If you want, I can **draw diagrams** showing memory layout for these programs so you can visualize how numbers and strings are stored. That will make them super easy to understand.



NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN



## for 16 bit

Perfect 👍
I’ll explain both programs step by step in **very simple beginner-friendly language**, as if you are just starting out in engineering and learning Assembly Language.

---

## 📌 First Program (Addition with Carry Check)

### Code Summary

This program:

1. Takes two numbers (N1 = 0050H and N2 = 00F0H).
2. Adds them together.
3. Stores the result in **N3**.
4. If there’s a carry (when the sum is bigger than what one register can hold), it increases **N4** to record that carry.

---

### Explanation

* `DATA SEGMENT ... DATA ENDS` → This is where we keep our numbers.

  * N1 = 50H (80 in decimal)
  * N2 = F0H (240 in decimal)
  * N3, N4 = Empty (for storing answers).

* `CODE SEGMENT ... CODE ENDS` → This is where the instructions are written.

* `MOV AX, DATA` and `MOV DS, AX` → Setup step: Tells the CPU where our data (N1, N2) is stored.

* `XOR AX, AX` → Clears AX (makes AX = 0).

* `MOV BX, AX` → Clears BX too (BX = 0).

* `MOV AX, N1` → Loads N1 (50H) into AX.

* `ADD AX, N2` → Adds N2 (F0H) to AX.
  👉 So, AX = 50H + F0H = 140H (320 in decimal).
  But since AX is only 16-bit, it checks for carry.

* `JNC STOP` → "Jump if No Carry".
  If there is **no carry**, go to STOP.
  If there **is a carry**, continue.

* `INC BX` → If carry happens, increase BX (like a flag counter).

* `MOV N4, BX` → Store carry info in N4.

* `STOP: MOV N3, AX` → Store final result in N3.

* `MOV AH, 4CH / INT 21H` → End program.

✅ So, N3 = Result of addition, N4 = Carry info.

---

## 📌 Second Program (Subtraction with Borrow Check)

### Code Summary

This program:

1. Takes two numbers (N1 = 0080H, N2 = 0060H).
2. Subtracts them (N1 - N2).
3. Stores the result in **N3**.
4. If there’s a borrow (when we subtract a bigger number from a smaller one), it records it in **N4**.

---

### Explanation

* Same setup with `DATA SEGMENT`, `CODE SEGMENT`.

* `MOV AX, DATA` and `MOV DS, AX` → Setup step again.

* `XOR AX, AX` and `XOR BX, BX` → Clear AX and BX.

* `MOV AX, N1` → Put N1 (0080H = 128) in AX.

* `SUB AX, N2` → Subtract N2 (0060H = 96).
  👉 AX = 80H - 60H = 20H (32 in decimal).

* `JNC NO_BORROW` → If **no borrow**, jump to NO\_BORROW.
  If there **is a borrow**, then continue.

* `INC BX` → Increase BX if borrow happened.

* `MOV N4, BX` → Save borrow info in N4.

* `NO_BORROW: MOV N3, AX` → Save the result in N3.

* `MOV AH, 4CH / INT 21H` → End program.

✅ So, N3 = Result of subtraction, N4 = Borrow info.

---

## 🎯 Super Simple Analogy

Think of **AX** as your notebook where you do calculations.

* In the first program, you **add two numbers**. If the sum is too big to fit, you raise your hand (that’s the **carry** stored in N4).
* In the second program, you **subtract two numbers**. If you don’t have enough to subtract, you borrow from your friend (that’s the **borrow**, also stored in N4).

So:

* **Program 1 = Adding with carry check.**
* **Program 2 = Subtracting with borrow check.**

---

👉 Do you want me to also **show the actual final values of N3 and N4** after running both programs (with the given N1 and N2)?







NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
## AUG 7 viva qn

You're learning 8086 Assembly Language! Great step for low-level understanding of computers. I'll **explain each of your 3 programs line by line** as a beginner-friendly guide.


---

## ✅ **PROGRAM 1 — PRINT "HELLO WORLD!"**

### 🔷 CODE:

```asm
PROGRAM 
D SEGMENT 
STRING DB 'HELLO WORLD!$' 
D ENDS 
C SEGMENT 
ASSUME CS:C, DS:D 
START: 
MOV AX,D 
MOV DS,AX 
LEA DX,STRING 
MOV AH,09H 
INT 21H 
MOV AH,4CH 
INT 21H 
C ENDS 
END START 
```

### 🔷 OUTPUT:

```
HELLO WORLD!
```

---

### 🧠 **Explanation:**

* `PROGRAM` — Label for the program (optional).
* `D SEGMENT` — Define **Data Segment** (`D`), where we store variables/data.
* `STRING DB 'HELLO WORLD!$'` — Create a string constant that ends with `$` (DOS needs `$` to know where the string ends).
* `D ENDS` — End of Data Segment.

---

### ▶ CODE Segment (Executable Instructions):

* `C SEGMENT` — Define Code Segment.
* `ASSUME CS:C, DS:D` — Tell assembler that:

  * `CS` (Code Segment) = `C`
  * `DS` (Data Segment) = `D`

---

### ▶ Execution begins at `START:` label:

* `MOV AX,D` — Move address of Data Segment `D` to AX register.
* `MOV DS,AX` — Set DS register to point to data segment.
* `LEA DX,STRING` — Load the address of the string into DX.
* `MOV AH,09H` — Tell DOS that you want to print a string (`09H` is print service).
* `INT 21H` — Call DOS interrupt to do the print.
* `MOV AH,4CH` — Tell DOS you want to exit the program.
* `INT 21H` — Exit the program.
* `C ENDS` / `END START` — Marks end of code and where execution begins.

---

## ✅ **PROGRAM 2 — ADDITION with CARRY DETECTION**

```asm
DATA SEGMENT 
N1 DW 0050H 
N2 DW 00F0H 
N3 DW ? 
N4 DW ? 
DATA ENDS 
```

### ➕ Two numbers to add:

* `N1 = 0050H (80)`
* `N2 = 00F0H (240)`
* `N3` will hold **sum**
* `N4` will hold **carry (BX)**

---

### 🧠 **Code Explanation:**

```asm
CODE SEGMENT 
ASSUME CS:CODE,DS:DATA 
START: 
MOV AX,DATA      ; Load address of data segment
MOV DS,AX        ; Set data segment
XOR AX,AX        ; Clear AX = 0
MOV BX,AX        ; Clear BX = 0
MOV AX,N1        ; AX = N1 = 0050H
ADD AX,N2        ; AX = AX + N2 = 0050 + 00F0 = 0140H
JNC STOP         ; If NO carry, jump to STOP
INC BX           ; If carry occurred, increment BX
MOV N4,BX        ; Store carry (0 or 1) to N4
STOP: 
MOV N3,AX        ; Store result (sum) to N3
MOV AH,4CH       ; Exit program
INT 21H 
CODE ENDS 
END START 
```

### 📤 **OUTPUT:**

* `N1 = 0050H = 80`
* `N2 = 00F0H = 240`
* `N3 = 0140H = 320`
* `N4 = 0` (no carry occurred since sum < 0xFFFF)

---

## ✅ **PROGRAM 3 — SUBTRACTION with BORROW DETECTION**

```asm
DATA SEGMENT 
N1 DW 00F0H 
N2 DW 0050H 
N3 DW ? 
N4 DW ? 
DATA ENDS 
```

### ➖ Two numbers to subtract:

* `N1 = 00F0H (240)`
* `N2 = 0050H (80)`
* `N3` will hold result
* `N4` will hold borrow flag (BX)

---

### 🧠 **Code Explanation:**

```asm
CODE SEGMENT 
ASSUME CS:CODE, DS:DATA 
START: 
MOV AX, DATA     ; Load address of data segment
MOV DS, AX       ; Set DS
XOR AX, AX       ; Clear AX
XOR BX, BX       ; Clear BX
MOV AX, N1       ; AX = N1 = 00F0
SUB AX, N2       ; AX = AX - N2 = 00F0 - 0050 = 00A0
JNC NO_BORROW    ; Jump if no borrow
INC BX           ; If borrow occurred, BX++
NO_BORROW: 
MOV N4, BX       ; Store borrow status in N4
MOV N3, AX       ; Store result in N3
MOV AH, 4CH      ; Exit
INT 21H 
CODE ENDS 
END START 
```

### 📤 **OUTPUT:**

* `N3 = 00A0H (160)`
* `N4 = 0` (no borrow occurred)

---

## ✅ SUMMARY FOR BEGINNERS:

| Concept        | Meaning                                           |
| -------------- | ------------------------------------------------- |
| `SEGMENT/ENDS` | Group data or code together                       |
| `ASSUME`       | Tell assembler what `CS` and `DS` point to        |
| `MOV`          | Move data between registers/memory                |
| `XOR AX, AX`   | Clear register AX (make it 0)                     |
| `INT 21H`      | Call DOS services (like print or exit)            |
| `ADD`, `SUB`   | Add or Subtract numbers                           |
| `JNC`          | Jump if no carry (for add) or no borrow (for sub) |
| `LEA`          | Load memory address                               |

---

If you'd like me to **draw memory layout or animation of what happens step by step**, just ask!
