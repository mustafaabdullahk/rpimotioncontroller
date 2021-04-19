#!/usr/bin/python
# -*- coding:utf-8 -*-

import time
import ADS1256
import DAC8532
import RPi.GPIO as GPIO
from concurrent import futures
import logging
import threading
import grpc
import motioncontroller_pb2
import motioncontroller_pb2_grpc


class Greeter(motioncontroller_pb2_grpc.DeviceService):
    def __init__(self):
        self.ADC = ADS1256.ADS1256()
        self.DAC = DAC8532.DAC8532()
        ADC.ADS1256_init()

    def SayHello(self, request, context):
        return motioncontroller_pb2.HelloReply(message="Test %s!" % request.name)

    def OutVoltage(self, request, context):
        DAC.DAC8532_Out_Voltage(DAC8532.channel_A, request.channel_voltage)
        return motioncontroller_pb2.CommandResult(
            command_result="Set voltage : %s" % request.channel_name
        )

    def GetDigitalValues(self, request, context):
        ADC_Value = ADC.ADS1256_GetAll()

        def response_message():
            response = motioncontroller_pb2.Analog2Digital(
                channel_voltage_1=ADC_Value[0] * 5.0 / 0x7FFFFF,
                channel_voltage_2=ADC_Value[1] * 5.0 / 0x7FFFFF,
                channel_voltage_3=ADC_Value[2] * 5.0 / 0x7FFFFF,
                channel_voltage_4=ADC_Value[3] * 5.0 / 0x7FFFFF,
                channel_voltage_5=ADC_Value[4] * 5.0 / 0x7FFFFF,
                channel_voltage_6=ADC_Value[5] * 5.0 / 0x7FFFFF,
                channel_voltage_7=ADC_Value[6] * 5.0 / 0x7FFFFF,
                channel_voltage_8=ADC_Value[7] * 5.0 / 0x7FFFFF,
            )
            yield response

        return response_message()


def mcserver():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    motioncontroller_pb2_grpc.add_DeviceServiceServicer_to_server(Greeter(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()


try:
    ADC = ADS1256.ADS1256()
    DAC = DAC8532.DAC8532()
    ADC.ADS1256_init()
    serverThread = threading.Thread(target=mcserver)
    serverThread.start()
    logging.basicConfig(filename= 'cmod_log', encoding= 'utf-8', level= logging.DEBUG)
    DAC.DAC8532_Out_Voltage(0x30, 3)
    DAC.DAC8532_Out_Voltage(0x34, 3)
    while 1:
        ADC_Value = ADC.ADS1256_GetAll()
        print("0 ADC = %lf" % (ADC_Value[0] * 5.0 / 0x7FFFFF))
        print("1 ADC = %lf" % (ADC_Value[1] * 5.0 / 0x7FFFFF))
        print("2 ADC = %lf" % (ADC_Value[2] * 5.0 / 0x7FFFFF))
        print("3 ADC = %lf" % (ADC_Value[3] * 5.0 / 0x7FFFFF))
        print("4 ADC = %lf" % (ADC_Value[4] * 5.0 / 0x7FFFFF))
        print("5 ADC = %lf" % (ADC_Value[5] * 5.0 / 0x7FFFFF))
        print("6 ADC = %lf" % (ADC_Value[6] * 5.0 / 0x7FFFFF))
        print("7 ADC = %lf" % (ADC_Value[7] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[0] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[1] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[2] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[3] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[4] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[5] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[6] * 5.0 / 0x7FFFFF))
        logging.debug((ADC_Value[7] * 5.0 / 0x7FFFFF))
        temp = (ADC_Value[0] >> 7) * 5.0 / 0xFFFF
        print("DAC :", temp)
        print("\33[10A")
        # DAC.DAC8532_Out_Voltage(DAC8532.channel_A, temp )
        DAC.DAC8532_Out_Voltage(DAC8532.channel_B, 3.3 - temp)

except:
    GPIO.cleanup()
    print("\r\nProgram end     ")
    exit()
