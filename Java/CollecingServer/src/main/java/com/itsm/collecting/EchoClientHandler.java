package com.itsm.collecting;

import org.apache.log4j.Logger;

import io.netty.buffer.ByteBuf;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.util.CharsetUtil;

public class EchoClientHandler extends SimpleChannelInboundHandler<ByteBuf> {

	private static final Logger logger =Logger.getLogger(EchoClientHandler.class);
	@Override
	protected void channelRead0(ChannelHandlerContext ctx, ByteBuf in) throws Exception {
		// TODO Auto-generated method stub
		logger.info("Client received:"+ in.toString(CharsetUtil.UTF_8));
	}
	
	@Override
	public void channelActive(ChannelHandlerContext ctx){
		logger.info(ctx);
		ctx.writeAndFlush(Unpooled.copiedBuffer("Netty rocks!\r\n",CharsetUtil.UTF_8));
		logger.info(ctx);
	}
	
	@Override
	public void exceptionCaught(ChannelHandlerContext ctx,Throwable cause){
		logger.error(cause);
		ctx.close();
	}
	
	

}
