#include <QCoreApplication>
#include <QDebug>

#include <motioncontroller.grpc.pb.h>
#include <motioncontroller.pb.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>
#include <thread>

#include "drivers/dac8532.h"
#include "3rdparty/debug.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;


void runMyServer(motioncontroller::DeviceService::Service *myserv)
{
	std::string ap = "0.0.0.0:50051";
	ServerBuilder builder;
	builder.AddListeningPort(ap, grpc::InsecureServerCredentials());
	builder.RegisterService(myserv);
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << ap << std::endl;
	server->Wait();
}

class RaspberryServer : public motioncontroller::DeviceService::Service
{
public:
	grpc::Status SayHello(grpc::ServerContext *context, const motioncontroller::HelloRequest *request, motioncontroller::HelloReply *response);
	grpc::Status GetDigitalValues(grpc::ServerContext *context, const google::protobuf::Empty *request, ::grpc::ServerWriter<motioncontroller::Analog2Digital> *writer);
	grpc::Status OutVoltage(grpc::ServerContext *context, const motioncontroller::Digital2Analog *request, motioncontroller::CommandResult *response);
	grpc::Status ConfigureAnalog2Digital(grpc::ServerContext *context, const motioncontroller::Analog2DigitalConfig *request, motioncontroller::CommandResult *response);
	grpc::Status SetDiffChannel(grpc::ServerContext *context, const motioncontroller::SetDiffChnAnalog2Digital *request, motioncontroller::CommandResult *response);
};

grpc::Status RaspberryServer::SayHello(grpc::ServerContext *context, const motioncontroller::HelloRequest *request, motioncontroller::HelloReply *response)
{
	qDebug()<< "hello";
	return grpc::Status::OK;
}

grpc::Status RaspberryServer::GetDigitalValues(grpc::ServerContext *context, const google::protobuf::Empty *request, ::grpc::ServerWriter<motioncontroller::Analog2Digital> *writer)
{
}

grpc::Status RaspberryServer::OutVoltage(grpc::ServerContext *context, const motioncontroller::Digital2Analog *request, motioncontroller::CommandResult *response)
{
	dac8532 dac;
	dac.outVoltage(channel_A, 3.3);
	dac.outVoltage(channel_B, request->channel_voltage());
	std::cout << "set voltage : " << request->channel_voltage() << std::endl;
	response->set_command_result("ok");
	return grpc::Status::OK;
}

grpc::Status RaspberryServer::ConfigureAnalog2Digital(grpc::ServerContext *context, const motioncontroller::Analog2DigitalConfig *request, motioncontroller::CommandResult *response)
{
}

grpc::Status RaspberryServer::SetDiffChannel(grpc::ServerContext *context, const motioncontroller::SetDiffChnAnalog2Digital *request, motioncontroller::CommandResult *response)
{
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	loguru::g_stderr_verbosity = 3;
	loguru::init(argc, argv);
	gInfoS() << "cilettttt";
	std::thread threadServer([=]() { runMyServer(new RaspberryServer); });
	return a.exec();
}
