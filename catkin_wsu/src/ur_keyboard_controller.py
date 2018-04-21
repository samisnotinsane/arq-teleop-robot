import sys,tty,termios,os



class _Getch:
    def __call__(self):
            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(1)
            finally:
                termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
            return ch

def get():
        inkey = _Getch()
        zvar = 0.2
        yvar = -0.3
        xvar = 0.4
        var = 1
        while(var == 1):
                k=inkey()
                if k=='u':
                        zvar += 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='j':
                        zvar -= 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='d':
                        yvar += 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='a':
                        yvar -= 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='s':
                        xvar += 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='w':
                        xvar -= 0.1
                        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[" + str(xvar) + "," + str(yvar) + ", "+ str(zvar) + "]' '[0.0, 0.0, 0.0, 0.0]'")
                elif k=='x':
                        sys.exit()

                #rostopic pub --once /positioner/position geometry_msgs/Pose -- '[0.4, -0.3, 0.2]' '[0.0, 0.0, 0.0, 0.0]'

def main():
        os.system("rostopic pub --once /positioner/position geometry_msgs/Pose -- '[0.4, -0.3, 0.2]' '[0.0, 0.0, 0.0, 0.0]'")
        get()

if __name__=='__main__':
        main()
