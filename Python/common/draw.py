# -*- coding:utf-8 -*-
import sys
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from matplotlib.ticker import FixedLocator, MultipleLocator, FormatStrFormatter, NullLocator, LinearLocator

import numpy as np
from datetime import datetime
import pylab

reload(sys)
sys.setdefaultencoding("utf-8")

def constructNewDict(time, num_of_char, connect_time, total_time, city_dict):
    result = list()
    result.append(connect_time)
    result.append(total_time)
    num_of_char_dict = dict()
    num_of_char_dict[num_of_char] = result
    city_dict[time] = num_of_char_dict

def rerangeDict(value, new_dict_data):

    for i in  range(len(value)):
        l = value[i]
        if (len(l) == 5):
            time = l[0]
            city = l[1]
            num_of_char = l[2]
            connect_time = l[3]
            total_time = l[4]
            if (new_dict_data.has_key(city)):
                constructNewDict(time, num_of_char, connect_time, total_time, new_dict_data[city])
            else:
                new_dict_data[city] = dict()
        else:
            print "items error ", l
    return new_dict_data

def parseDataFromTxt(file_name):
    f = file(file_name)
    city_data = dict()

    for each_line in f:
        line_of_string = each_line.split()
        if len(line_of_string) == 5:
            city = line_of_string[1]
            if city_data.has_key(city):
                city_data[city].append(line_of_string)
            else:
                city_data[city] = list()

    # print city_data
    new_dict_data = dict()
    for pos in city_data:
        rerangeDict(city_data[pos], new_dict_data)
    return new_dict_data


def getTotalTimePerCity(time, num_of_char, data):
    if data[time].has_key(str(num_of_char)):
        return data[time][str(num_of_char)][1]
    else:
        return -1


def getConnectTimePerCity(time, num_of_char, data):
    if data[time].has_key(str(num_of_char)):
        return data[time][str(num_of_char)][0]
    else:
        return -1


def plotPicuterPerCity(city, value, english_name):
    time = list(value.keys())
    connect_time = list()
    total_time = list()
    plot_time = list()
    for t in range(len(time)):
        total = getTotalTimePerCity(time[t], 1024, value)
        connect = getConnectTimePerCity(time[t], 1024, value)
        if total != -1 and connect != -1:
            total_time.append(total)
            connect_time.append(connect)
            plot_time.append(time[t])

    plot_time_dict = dict()
    for i in range(len(plot_time)):
        plot_time_dict[plot_time[i]] = i

    sorted_plot_time_keys = sorted(plot_time_dict.keys())
    print sorted_plot_time_keys

    new_connect_time = list()
    new_total_time = list()
    data_transmition_time  = list()

    for i in range(len(sorted_plot_time_keys)):
        key = sorted_plot_time_keys[i]
        pos = plot_time_dict[key]
        new_connect_time.append(float(connect_time[pos]))
        new_total_time.append(float(total_time[pos]))
        data_transmition_time.append(float(total_time[pos]) - float(connect_time[pos]))

    plot_time_str = list()


    plt.rcParams['figure.figsize'] = (18.0, 12.0)
    plt.rcParams['figure.dpi'] = 300
    plt.clf()


    for i in range(len(sorted_plot_time_keys)):
        d = datetime.fromtimestamp(float(sorted_plot_time_keys[i]))
        str1 = d.strftime("%Y-%m-%d %H:%M")
        plot_time_str.append(d)

    xs = plot_time_str
    # 设置日期的显示格式
    date_format = mpl.dates.DateFormatter("%Y-%m-%d %H:%M")
    plt.gca().xaxis.set_major_formatter(date_format)
    plt.gca().xaxis.set_major_locator(mdates.MinuteLocator(interval=40))
    plt.gca().yaxis.set_major_locator(LinearLocator(numticks=20))
    # plt.gca().yaxis.set_minor_locator(NullLocator())

    plt.title("Connect over the Internet from Silicon Valley to " + english_name + "(Message Size: 1024 Bytes)")
    plt.plot(plot_time_str, new_connect_time, 'g--', markeredgecolor='black', marker = "o", label = "connect time")
    plt.plot(plot_time_str, new_total_time, 'b--', marker="x", label = "total time")
    plt.legend(['Connect Delay', 'Total Delay'], loc='upper right')
    plt.ylabel("Time(seconds)")

    plt.savefig(english_name, bbox_inches='tight')


    f = open("delay.txt", "a+")
    print >> f, "city, ", city, " connection time ", sum(new_connect_time) / float(len(new_connect_time))
    print >> f, "city, ", city, " data transmission time", sum(data_transmition_time) / float(len(data_transmition_time))
    total_time_in_seconds = 0.0
    for i in range(len(total_time)):
        total_time_in_seconds += float(total_time[i])
    print >> f, "city, ", city, " delay time ", total_time_in_seconds / len(total_time)


def plotPictureByCity(dict_result, english_name):
    for city in dict_result:
        plotPicuterPerCity(city, dict_result[city], english_name)

def main():
    data_list = ["Ohio", "Oregon", "California", "Virginia"]

    for i in range(len(data_list)):
        dict_result = parseDataFromTxt(data_list[i] + ".txt")
        plotPictureByCity(dict_result, data_list[i])


if __name__ == "__main__":
        main()
