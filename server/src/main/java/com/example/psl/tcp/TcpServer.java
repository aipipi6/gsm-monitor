package com.example.psl.tcp;

import java.net.InetSocketAddress;

import io.netty.bootstrap.ServerBootstrap;
import io.netty.buffer.ByteBuf;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.ChannelOption;
import io.netty.channel.ChannelPipeline;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.handler.codec.LengthFieldBasedFrameDecoder;
import io.netty.handler.codec.LengthFieldPrepender;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.handler.codec.string.StringEncoder;

public class TcpServer {
	public static void start(int port) {
		// boss线程监听端口，worker线程负责数据读写
		EventLoopGroup boss = new NioEventLoopGroup();
		EventLoopGroup worker = new NioEventLoopGroup();

		try {
			// 辅助启动类
			ServerBootstrap bootstrap = new ServerBootstrap();
			// 设置线程池
			bootstrap.group(boss, worker);

			// 设置socket工厂
			bootstrap.channel(NioServerSocketChannel.class);

			// 设置管道工厂
			bootstrap.childHandler(new ChannelInitializer<SocketChannel>() {
				@Override
				protected void initChannel(SocketChannel socketChannel) throws Exception {
					// 获取管道
					ChannelPipeline pipeline = socketChannel.pipeline();
					// // 字符串解码器
					// pipeline.addLast(new StringDecoder());
					// // 字符串编码器
					// pipeline.addLast(new StringEncoder());
					//pipeline.addLast("frameDecoder", new LengthFieldBasedFrameDecoder(Integer.MAX_VALUE, 0, 4, 0, 4));
					//pipeline.addLast("frameEncoder", new LengthFieldPrepender(4));
					// 处理类
					pipeline.addLast(new ServerHandler());
				}
			});

			// 设置TCP参数
			// 1.链接缓冲池的大小（ServerSocketChannel的设置）
			bootstrap.option(ChannelOption.SO_BACKLOG, 1024);
			// 维持链接的活跃，清除死链接(SocketChannel的设置)
			bootstrap.childOption(ChannelOption.SO_KEEPALIVE, true);
			// 关闭延迟发送
			bootstrap.childOption(ChannelOption.TCP_NODELAY, true);

			// 绑定端口
			ChannelFuture future = bootstrap.bind(port).sync();
			System.out.println("Tcp server start ...... ");

			// 等待服务端监听端口关闭
			future.channel().closeFuture().sync();

		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {
			// 优雅退出，释放线程池资源
			boss.shutdownGracefully();
			worker.shutdownGracefully();
		}
	}

	static class ServerHandler extends SimpleChannelInboundHandler<ByteBuf> {

		@Override
		protected void channelRead0(ChannelHandlerContext ctx, ByteBuf msg) throws Exception {
			// TODO Auto-generated method stub
			byte[] result = new byte[msg.readableBytes()];
			msg.readBytes(result);
			System.out.println("client response :" + new String(result));
			
			// ctx.channel().writeAndFlush("i am server !");
			ctx.channel().flush();
		}

		// 新客户端接入
		@Override
		public void channelActive(ChannelHandlerContext ctx) throws Exception {
			InetSocketAddress insocket = (InetSocketAddress) ctx.channel().remoteAddress();
			String clientIP = insocket.getAddress().getHostAddress();
			System.out.println("channelActive:" + clientIP);
		}

		// 客户端断开
		@Override
		public void channelInactive(ChannelHandlerContext ctx) throws Exception {
			InetSocketAddress insocket = (InetSocketAddress) ctx.channel().remoteAddress();
			String clientIP = insocket.getAddress().getHostAddress();
			System.out.println("channelInactive:" + clientIP);
		}

		// 异常
		@Override
		public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
			// 关闭通道
			ctx.channel().close();
			// 打印异常
			cause.printStackTrace();
		}
	}
}
