!utest_proto_include_guard {
	CONFIG +=  utest_proto_include_guard
	SOURCES += \
		$$PWD/motioncontroller.pb.cc \
		$$PWD/motioncontroller.grpc.pb.cc \

	HEADERS += \
		$$PWD/motioncontroller.grpc.pb.h \
		$$PWD/motioncontroller.pb.h \

	INCLUDEPATH += $$PWD
	LIBS += -lprotobuf -lgrpc++
} 
