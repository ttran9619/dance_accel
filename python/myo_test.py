

myo.vibrate(4)

while(True):
    x, y, z = myo.getAccel()
    print("X: " + str(x) + '\n')
    print("Y: " + str(y) + '\n')
    print("Z: " + str(z) + '\n')