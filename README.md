# Arduino-Python_Monitoring
Python 3.5 for Windows.
Python modules requiered:
  pip install prettytable
  pip install pymysql
  pip install socket
  pip install flask
  
Steps
1. Import into MySQL Server ArduinoDB.sql
2. Creatr MySQL User arduino / password arduino
3. Edit IP in Arduino_Files\MegaEtherAlarm\MegaEtherAlarm.ino line 14
4. Edit IP configured in Step 3 in Python_Scripts\arduino.py
5. Edit yout Host IP in Fserver.py 
6. Run GUI_Test\dist\GUI_Test.jar
