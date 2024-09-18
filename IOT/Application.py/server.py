from flask import Flask , request, jsonify
from dbutils.execute import execute_query, execute_select_query
from dbutils.connection import get_connection
import paho.mqtt.client as mqtt
srv = Flask(__name__)

@srv.route('/', methods=['GET'])
def homepage():

    return "Welcome to Fitness Tracker"
@srv.route('/add', methods=['POST'])
def add_info():
    name = request.get_json().get('name')
    age = request.get_json().get('age')
    city = request.get_json().get('city')
    steps = request.get_json().get('steps')
    pulse = request.get_json().get('pulse')
    oxygen = request.get_json().get('oxygen')
    temp = request.get_json().get('temp')
    
    query=f"insert into health(name, age, city, steps, pulse, oxygen, temp) values('{name}',{age},'{city}',{steps},{pulse},{oxygen},{temp});"

    execute_query(query)
    return "Healty parameters are successfully added"


@srv.route('/all', methods=['GET'])
def get_all():
    
    return jsonify(execute_select_query(query))    


@srv.route('/info', methods=['GET'])
def get_info():
    name = request.get_json().get('name')

    query =f"select * from health where name = '{name}';"
    return jsonify(execute_select_query(query))

@srv.route('/update', methods=['PUT'])
def update_city():    
    name = request.get_json().get('name')
    city = request.get_json().get('city')

    query = f"update health SET city ='{city} where name ='{name}';"
    execute_query(query)
    return f"city of {name}is updated as {city}"

@srv.route('/steps', methods=['GET'])
def get_steps():
    query=f"select * health order by steps DESC limit 1;"
    return jsonify(execute-select-query(query))

if __name__=='__main__':
    srv.run(host='0.0.0.0', port=3000, debug=True)   
