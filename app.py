from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import wiringpi as wp
import datetime

app = Flask(__name__) #파일이름
socketio = SocketIO(app)

LED_PIN = 7
SPI_CH = 0
ADC_CH_LIGHT = 0
ADC_CS = 29
SPI_SPEED = 500000
wp.wiringPiSetup()
wp.wiringPiSPISetup(SPI_CH, SPI_SPEED)
wp.pinMode(LED_PIN, 1)
wp.pinMode(ADC_CS, 1)

#=======================================================================
#				index.html
#=======================================================================
@app.route('/') 
def index(): #5555로 입장시 실행됨 
    """Serve the index HTML"""
    return render_template('index.html') # a.html도 가능 template디렉토리 안에 존재하는게 리턴됨 

#=======================================================================
#				led action + response
#=======================================================================
@app.route("/led1/<led_state>") # <led_state>변수가 됨 
def control_led_action(led_state):
    print("control_led_action") #checkbox 누른 경우 실행 
    
    if led_state == "true": 
        print("action==true")
        wp.digitalWrite(LED_PIN, 1) #wiringpi로 동작 시킴 
        ledS="ON"      
    else: 
        print("action==false")
        wp.digitalWrite(LED_PIN, 0)
        ledS="OFF"
      
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M:%S")
    templateData = { #dictionary타입 - 키-밸류 쌍 
      'time': timeString ,
      'ledS' : ledS
    }                  
    return render_template('ajax_led_response.html',**templateData) # **는 딕셔너리를 넘겨줄때 사용된다?

@app.route('/iot_with_flask.js') #같은 이름으ㅡ로 리턴되는게 아니라 여기있는 부분이 리턴됨 
def gauge():
    return render_template('iot_with_flask.js') #여기있는 argument 부분이 리턴됨 

#=======================================================================
#				socketio ( websocket ) 
#=======================================================================
@socketio.on('measurement_start')
def on_create(data):
    print("measurement_start")
    it=data['iterations']
    for i in range(it):
        wp.digitalWrite(ADC_CS, 1)
        buf = bytearray(3)
        buf[0] = 0x06 | ((ADC_CH_LIGHT & 0x04)>>2)
        buf[1] = ((ADC_CH_LIGHT & 0x03)<<6)
        buf[2] = 0x00
        wp.digitalWrite(ADC_CS,0)
        ret_len, buf = wp.wiringPiSPIDataRW(SPI_CH, bytes(buf))
        buf = bytearray(buf)
        buf[1] = 0x0F & buf[1]
        #value=(buf[1] << 8) | buf[2]
        light_val = int.from_bytes(bytes(buf), byteorder='big')
        wp.digitalWrite(ADC_CS,1)
        print("light value=", light_val)
        socketio.sleep(.2)
        emit('msg_from_server', {'lightVal': light_val})

#=======================================================================        
if __name__ == '__main__': #이게 젤 처음 돌아가는것임
    socketio.run(app, host='0.0.0.0', port=5555, debug=False)
