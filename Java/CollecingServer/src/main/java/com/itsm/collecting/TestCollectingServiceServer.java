package com.itsm.collecting;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Future;
import java.util.concurrent.ScheduledExecutorService;

import org.apache.log4j.Logger;

import com.itsm.collecting.util.TestCollectingServiceHandler;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.handler.codec.LineBasedFrameDecoder;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.util.CharsetUtil;

/**
 * Created by CM on 2016/8/25.
 */
public class TestCollectingServiceServer {
    private final int port;
    private final ScheduledExecutorService host_es;
    private final ScheduledExecutorService db_es;
    private final ConcurrentHashMap<String,Future> host_future_map ;
    private final ConcurrentHashMap<String,Future> db_future_map;
    
    private static Logger logger = Logger.getLogger(TestCollectingServiceServer.class);
    public TestCollectingServiceServer(int port,ScheduledExecutorService host_es,ScheduledExecutorService db_es,ConcurrentHashMap<String,Future> host_future_map,ConcurrentHashMap<String,Future> db_future_map) {
        this.port = port;
        this.host_es =host_es;
        this.db_es = db_es;
        this.host_future_map = host_future_map;
        this.db_future_map = db_future_map;
    }

    public void start() throws Exception {
        EventLoopGroup group = new NioEventLoopGroup();

        try {
            ServerBootstrap b = new ServerBootstrap();
            b.group(group).channel(NioServerSocketChannel.class).localAddress(port)
                    .childHandler(new ChannelInitializer<Channel>() {
                        @Override
                        protected void initChannel(Channel ch) throws Exception {
                            ChannelPipeline pipeline = ch.pipeline();
                             pipeline.addLast(LineBasedFrameDecoder.class.getName(), new LineBasedFrameDecoder(256));
                             pipeline.addLast(StringDecoder.class.getName(), new StringDecoder(CharsetUtil.UTF_8));
                             pipeline.addLast(new TestCollectingServiceHandler(host_es,db_es,host_future_map,db_future_map));
                        }

                    });
            ChannelFuture f = b.bind().sync();
            f.channel().closeFuture().sync();
        } finally {
            group.shutdownGracefully();
        }
    }
}
