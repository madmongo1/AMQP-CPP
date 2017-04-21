cmake_minimum_required(VERSION 3.0)

project(amqp-cpp)

if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif ()

prefix_files(include PREFIX "include" APPEND PUBLIC_INTERFACE FILES amqpcpp.h)
prefix_files(include.amqpcpp PREFIX "include/amqpcpp" APPEND PRIVATE_INTERFACE_FILES FILES
        address.h
        array.h
        booleanset.h
        buffer.h
        bytebuffer.h
        callbacks.h
        channel.h
        channelimpl.h
        classes.h
        endian.h
        connection.h
        connectionhandler.h
        connectionimpl.h
        copiedbuffer.h
        decimalfield.h
        deferred.h
        deferredcancel.h
        deferredconsumer.h
        deferredconsumerbase.h
        deferreddelete.h
        deferredget.h
        deferredqueue.h
        entityimpl.h
        envelope.h
        exception.h
        exchangetype.h
        field.h
        fieldproxy.h
        flags.h
        frame.h
        login.h
        message.h
        metadata.h
        monitor.h
        numericfield.h
        outbuffer.h
        protocolexception.h
        receivedframe.h
        stack_ptr.h
        stringfield.h
        table.h
        tcpchannel.h
        tcpconnection.h
        tcpdefines.h
        tcphandler.h
        watchable.h)
prefix_files(src PREFIX "src" APPEND SOURCE_FILES FILES
        addressinfo.h
        array.cpp
        basicackframe.h
        basiccancelframe.h
        basiccancelokframe.h
        basicconsumeframe.h
        basicconsumeokframe.h
        basicdeliverframe.h
        basicframe.h
        basicgetemptyframe.h
        basicgetframe.h
        basicgetokframe.h
        basicheaderframe.h
        basicnackframe.h
        basicpublishframe.h
        basicqosframe.h
        basicqosokframe.h
        basicrecoverasyncframe.h
        basicrecoverframe.h
        basicrecoverokframe.h
        basicrejectframe.h
        basicreturnframe.h
        bodyframe.h
        channelcloseframe.h
        channelcloseokframe.h
        channelflowframe.h
        channelflowokframe.h
        channelframe.h
        channelimpl.cpp
        channelopenframe.h
        channelopenokframe.h
        connectioncloseframe.h
        connectioncloseokframe.h
        connectionframe.h
        connectionimpl.cpp
        connectionopenframe.h
        connectionopenokframe.h
        connectionsecureframe.h
        connectionsecureokframe.h
        connectionstartframe.h
        connectionstartokframe.h
        connectiontuneframe.h
        connectiontuneokframe.h
        consumedmessage.h
        deferredcancel.cpp
        deferredconsumer.cpp
        deferredconsumerbase.cpp
        deferredget.cpp
        exchangebindframe.h
        exchangebindokframe.h
        exchangedeclareframe.h
        exchangedeclareokframe.h
        exchangedeleteframe.h
        exchangedeleteokframe.h
        exchangeframe.h
        exchangeunbindframe.h
        exchangeunbindokframe.h
        extframe.h
        field.cpp
        flags.cpp
        framecheck.h
        headerframe.h
        heartbeatframe.h
        includes.h
        methodframe.h
        passthroughbuffer.h
        pipe.h
        protocolheaderframe.h
        queuebindframe.h
        queuebindokframe.h
        queuedeclareframe.h
        queuedeclareokframe.h
        queuedeleteframe.h
        queuedeleteokframe.h
        queueframe.h
        queuepurgeframe.h
        queuepurgeokframe.h
        queueunbindframe.h
        queueunbindokframe.h
        receivedframe.cpp
        reducedbuffer.h
        returnedmessage.h
        table.cpp
        tcpclosed.h
        tcpconnected.h
        tcpinbuffer.h
        tcpoutbuffer.h
        tcpresolver.h
        tcpstate.h
        transactioncommitframe.h
        transactioncommitokframe.h
        transactionframe.h
        transactionrollbackframe.h
        transactionrollbackokframe.h
        transactionselectframe.h
        transactionselectokframe.h
        watchable.cpp
        tcpconnection.cpp)

option(BUILD_SHARED "build shared library" OFF)

if (BUILD_SHARED)
    add_library(amqp-cpp SHARED ${SOURCE_FILES} ${PRIVATE_INTERFACE_FILES} ${PUBLIC_INTERFACE_FILES})
    set_target_properties(amqp-cpp PROPERTIES SOVERSION 2.6)
    install(TARGETS amqp-cpp
            LIBRARY DESTINATION lib
            )
else ()
    add_library(amqp-cpp STATIC ${SOURCE_FILES} ${PRIVATE_INTERFACE_FILES} ${PUBLIC_INTERFACE_FILES})
    install(TARGETS amqp-cpp
            ARCHIVE DESTINATION lib
            )
endif ()
target_include_directories(amqp-cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(amqp-cpp SYSTEM PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories(amqp-cpp SYSTEM PUBLIC $<INSTALL_INTERFACE:include>)

Include_directories(${PROJECT_SOURCE_DIR})
install(DIRECTORY include/amqpcpp DESTINATION include/amqpcpp
        FILES_MATCHING PATTERN "*.h")
install(FILES include/amqpcpp.h DESTINATION include)

option(BUILD_TUTORIALS "build rabbitmq tutorials" OFF)
if (BUILD_TUTORIALS)
    #    add_subdirectory(examples/rabbitmq_tutorials)
endif ()

set(AMQP-CPP_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(AMQP-CPP_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

if (WIN32)
    add_definitions(-DNOMINMAX -DWIN32_LEAN_AND_MEAN)
endif ()
