package com.itsm.collecting.node;

import org.apache.log4j.Logger;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;

import java.util.List;

/**
 * Created by bruce on 16-11-25.
 */
/*
 * It's a class to watch Zookeeper client and master node
 */

