import serial

ser = serial.Serial('COM4', 9600)

while True:
    user_input = input("Enter a number (0-9), 'scroll' to enable scrolling, or 'exit' to quit: ")
    if user_input.lower() == 'exit':
        ser.write(bytes([10]))  # Sends 10 to turn off the nixie tube
        break
    elif user_input.lower() == 'scroll':
        ser.write(bytes([16]))  # Sends 16 to enable scrolling animation
    try:
        num = int(user_input)
        if 0 <= num <= 9:
            ser.write(bytes([num]))  # Sends the number as a single byte
        else:
            print("Please enter a number between 0 and 9.")
    except ValueError:
        print("Invalid input. Please enter a valid number.")

    # print(f"Response: {ser.readline().decode('utf-8').strip()}")
