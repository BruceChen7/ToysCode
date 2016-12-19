package com.itsm.collecting;

import org.apache.commons.cli.*;
import org.apache.log4j.Logger;

public class BootStrap {
	private static Logger logger = Logger.getLogger(BootStrap.class);

    public static void main(String[] args) {

        Option help = new Option("help", "print this help message");
        Option version = new Option("version",  "version of this service");
        Option mode = OptionBuilder.withArgName("mode")
                                    .hasArg()
                                    .withDescription("run as a mode which can be run as redis mode, host mode, db mode")
                                    .create("mode");

        Options op = new Options();
        op.addOption(help);
        op.addOption(version);
        op.addOption(mode);
        CommandLineParser parser = new DefaultParser();
        HelpFormatter format = new HelpFormatter();
        format.printHelp("collecting", op);

        try {
            CommandLine line = parser.parse(op, args);

            if(line.hasOption("mode")) {
                String m = line.getOptionValue("mode", "host");
                logger.info("m is " + m);

            } else {
                // run as collecting host data
            }
        } catch (ParseException e) {
            logger.info("parsing failed: reason " +  e.getMessage());
        }


    }
}
