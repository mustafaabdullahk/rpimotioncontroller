# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

from google.protobuf import empty_pb2 as google_dot_protobuf_dot_empty__pb2
import motioncontroller_pb2 as motioncontroller__pb2


class DeviceServiceStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.SayHello = channel.unary_unary(
                '/motioncontroller.DeviceService/SayHello',
                request_serializer=motioncontroller__pb2.HelloRequest.SerializeToString,
                response_deserializer=motioncontroller__pb2.HelloReply.FromString,
                )
        self.GetDigitalValues = channel.unary_unary(
                '/motioncontroller.DeviceService/GetDigitalValues',
                request_serializer=google_dot_protobuf_dot_empty__pb2.Empty.SerializeToString,
                response_deserializer=motioncontroller__pb2.Analog2Digital.FromString,
                )
        self.OutVoltage = channel.unary_unary(
                '/motioncontroller.DeviceService/OutVoltage',
                request_serializer=motioncontroller__pb2.Digital2Analog.SerializeToString,
                response_deserializer=motioncontroller__pb2.CommandResult.FromString,
                )
        self.ConfigureAnalog2Digital = channel.unary_unary(
                '/motioncontroller.DeviceService/ConfigureAnalog2Digital',
                request_serializer=motioncontroller__pb2.Analog2DigitalConfig.SerializeToString,
                response_deserializer=motioncontroller__pb2.CommandResult.FromString,
                )
        self.SetDiffChannel = channel.unary_unary(
                '/motioncontroller.DeviceService/SetDiffChannel',
                request_serializer=motioncontroller__pb2.SetDiffChnAnalog2Digital.SerializeToString,
                response_deserializer=motioncontroller__pb2.CommandResult.FromString,
                )


class DeviceServiceServicer(object):
    """Missing associated documentation comment in .proto file."""

    def SayHello(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def GetDigitalValues(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def OutVoltage(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def ConfigureAnalog2Digital(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def SetDiffChannel(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_DeviceServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'SayHello': grpc.unary_unary_rpc_method_handler(
                    servicer.SayHello,
                    request_deserializer=motioncontroller__pb2.HelloRequest.FromString,
                    response_serializer=motioncontroller__pb2.HelloReply.SerializeToString,
            ),
            'GetDigitalValues': grpc.unary_unary_rpc_method_handler(
                    servicer.GetDigitalValues,
                    request_deserializer=google_dot_protobuf_dot_empty__pb2.Empty.FromString,
                    response_serializer=motioncontroller__pb2.Analog2Digital.SerializeToString,
            ),
            'OutVoltage': grpc.unary_unary_rpc_method_handler(
                    servicer.OutVoltage,
                    request_deserializer=motioncontroller__pb2.Digital2Analog.FromString,
                    response_serializer=motioncontroller__pb2.CommandResult.SerializeToString,
            ),
            'ConfigureAnalog2Digital': grpc.unary_unary_rpc_method_handler(
                    servicer.ConfigureAnalog2Digital,
                    request_deserializer=motioncontroller__pb2.Analog2DigitalConfig.FromString,
                    response_serializer=motioncontroller__pb2.CommandResult.SerializeToString,
            ),
            'SetDiffChannel': grpc.unary_unary_rpc_method_handler(
                    servicer.SetDiffChannel,
                    request_deserializer=motioncontroller__pb2.SetDiffChnAnalog2Digital.FromString,
                    response_serializer=motioncontroller__pb2.CommandResult.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'motioncontroller.DeviceService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class DeviceService(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def SayHello(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/motioncontroller.DeviceService/SayHello',
            motioncontroller__pb2.HelloRequest.SerializeToString,
            motioncontroller__pb2.HelloReply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def GetDigitalValues(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/motioncontroller.DeviceService/GetDigitalValues',
            google_dot_protobuf_dot_empty__pb2.Empty.SerializeToString,
            motioncontroller__pb2.Analog2Digital.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def OutVoltage(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/motioncontroller.DeviceService/OutVoltage',
            motioncontroller__pb2.Digital2Analog.SerializeToString,
            motioncontroller__pb2.CommandResult.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def ConfigureAnalog2Digital(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/motioncontroller.DeviceService/ConfigureAnalog2Digital',
            motioncontroller__pb2.Analog2DigitalConfig.SerializeToString,
            motioncontroller__pb2.CommandResult.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def SetDiffChannel(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/motioncontroller.DeviceService/SetDiffChannel',
            motioncontroller__pb2.SetDiffChnAnalog2Digital.SerializeToString,
            motioncontroller__pb2.CommandResult.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)