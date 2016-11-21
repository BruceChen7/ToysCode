package com.itsm.collecting.util;

import org.apache.log4j.Logger;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 此类提供一些静态方法用于时间戳（10位整数）与Date类型的转换
 * @author 段庆元
 * 2016/1/14
 */
public class TimeTrans {
	private static Logger logger=Logger.getLogger(TimeTrans.class);
	/**
	 * 获取当前时间的时间戳
	 * @return int    当前时间的时间戳
	 */
	
	public static  int  getCurrentTimestamp()
	{
		long nowtime=System.currentTimeMillis();
		int  timestamp=(int)(nowtime/1000);
		return timestamp;	
	}


	/**
	 * 将时间戳类型转换为Date类型
	 * @param timestamp  用于转换的时间戳
	 * @return Date      转换后的Date 对象(失败返回null)
	 */
	public static Date TimestampToDate(int timestamp)
	{
		if(timestamp<=0)
		{
			logger.error("时间戳值不合法！");
			return null;
		}
		long time=(long)timestamp*1000;
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		String date=sdf.format(time);
		try {
			Date nowdate=sdf.parse(date);
			return nowdate;
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			logger.error("时间转换失败！");
			return null;
		}
	}
	/**
	 * 将Date类型对象转换为时间戳值
	 * @param date   用于转换的Date对象
	 * @return int   转换后的时间戳值（失败返回-1）
	 */
	public static int  DateToTimestamp(Date date)
	{
		if(date==null)
		{
			logger.error("日期对象不合法！");
			return -1;
		}
		long time=date.getTime();
		int timestamp=(int)(time/1000);
		return timestamp;
	}
	/**
	 * 将字符串形式的date转换为时间戳值
	 * @param date   用于转换的时间字符串
	 * @return int   转换后的时间戳值（失败返回-1）
	 */
	public static int DateToTimestamp(String date)
	{
		if(date==null)
		{
			logger.error("日期字符串为空！");
			return -1;
		}
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
		try {
			Date nowdate=sdf.parse(date);
			long time=nowdate.getTime();
			int timestamp=(int)(time/1000);
			return timestamp;
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			logger.error("日期转换失败！");
			return -1;
		}
	}



    /*
     * 将Date对象转成指定格式的字符串
     */
    public static String DateToString(Date date, String format) {

        SimpleDateFormat sdf = new SimpleDateFormat(format);

        return sdf.format(date);

    }


    public static String timeDifference(int end, int begin) {
        Date end_date = TimestampToDate(end);
        Date begin_date = TimestampToDate(begin);

        long end_msec = end_date.getTime();
        long start_msec = begin_date.getTime();

        long diff = end_msec - start_msec;

        long day =  diff / (24 * 60 * 60 * 1000);
        long left = diff % (24 * 60 * 60 * 1000);
        long hour = left / (60 * 60 * 1000);
        left =  left %(60 * 60 * 1000);
        long min = left / (60 * 1000);

        String res = "";
        if(day != 0) {
            res += day + "天";
        }

        if(hour != 0) {
            res += hour + "小时";
        }

        if(min != 0) {
            res += min + "分钟";
        }
        return res;

    }



    public static int StringToTimeStamp(String date, String format) {
        SimpleDateFormat sdf=new SimpleDateFormat(format);


        try {
            Date time = sdf.parse(date);
            long time_stamp = time.getTime();
            return (int)(time_stamp / 1000) ;
        } catch(ParseException e) {
            e.printStackTrace();
            logger.error("日期字符串转成时间戳失败");
            return -1;
        }

    }

	/**
	 * 将时间戳类型转换为yyyy-mm-dd hh:mm:ss 形式
	 * @param timestamp 时间戳值
	 * @return 
	 */
	public static String TimestamptoDateFormat(int timestamp)
	{
		Date tempdate=TimeTrans.TimestampToDate(timestamp);
		DateFormat dateformat=DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM);
		return dateformat.format(tempdate);
	}
	/**
	 * 将时间戳类型转换为yyyy-mm-dd 形式
	 * @param timestamp 时间戳值
	 * @return
	 */
	public static String TimestamptoOnlyDateFormat(int timestamp)
	{
		Date tempdate=TimeTrans.TimestampToDate(timestamp);
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
		return sdf.format(tempdate);
	}
	/**
	 * 将字符串形式的date转换为时间戳值
	 * @param date   用于转换的时间字符串
	 * @return int   转换后的时间戳值（失败返回-1）
	 */
	public static int DateTimeToTimestamp(String date)
	{
		if(date==null)
		{
			logger.error("日期字符串为空！");
			return -1;
		}
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try {
			Date nowdate=sdf.parse(date);
			long time=nowdate.getTime();
			int timestamp=(int)(time/1000);
			return timestamp;
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			logger.error("日期转换失败！");
			return -1;
		}
	}

	public static int ImportDateToTimeStamp(int daycounts){
		return (daycounts-25569)*86400;
	}
}
