CREATE DATABASE  IF NOT EXISTS `arduinodb` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `arduinodb`;
-- MySQL dump 10.13  Distrib 5.7.9, for Win64 (x86_64)
--
-- Host: localhost    Database: arduinodb
-- ------------------------------------------------------
-- Server version	5.7.10-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `b01r01`
--

DROP TABLE IF EXISTS `b01r01`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `b01r01` (
  `ID` smallint(6) NOT NULL AUTO_INCREMENT,
  `BinNumber` int(11) NOT NULL,
  `AnalogInput` int(11) NOT NULL,
  `BinStatusBit` int(11) NOT NULL DEFAULT '0',
  `BinStatus` varchar(45) NOT NULL,
  `TimeStamp` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `b01r01`
--

LOCK TABLES `b01r01` WRITE;
/*!40000 ALTER TABLE `b01r01` DISABLE KEYS */;
INSERT INTO `b01r01` VALUES (1,1,0,3,'UNKNOWN','2016-01-30 00:59:05'),(2,2,1,3,'UNKNOWN','2016-01-30 00:59:05'),(3,3,2,3,'UNKNOWN','2016-01-30 00:59:05'),(4,4,3,3,'UNKNOWN','2016-01-30 00:59:05'),(5,5,4,3,'UNKNOWN','2016-01-30 00:59:05'),(6,6,5,3,'UNKNOWN','2016-01-30 00:59:05'),(7,7,6,3,'UNKNOWN','2016-01-30 00:59:05'),(8,8,7,3,'UNKNOWN','2016-01-30 00:59:05'),(9,9,8,3,'UNKNOWN','2016-01-30 00:59:05'),(10,10,9,3,'UNKNOWN','2016-01-30 00:59:05'),(11,11,10,3,'UNKNOWN','2016-01-30 00:59:05'),(12,12,11,3,'UNKNOWN','2016-01-30 00:59:05'),(13,13,12,3,'UNKNOWN','2016-01-30 00:59:05'),(14,14,13,3,'UNKNOWN','2016-01-30 00:59:05'),(15,15,14,3,'UNKNOWN','2016-01-30 00:59:05'),(16,16,15,3,'UNKNOWN','2016-01-30 00:59:05');
/*!40000 ALTER TABLE `b01r01` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `bioterio_01`
--

DROP TABLE IF EXISTS `bioterio_01`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bioterio_01` (
  `ID` smallint(6) NOT NULL AUTO_INCREMENT,
  `RackName` varchar(8) NOT NULL DEFAULT '',
  `NodeNumber` int(11) NOT NULL,
  `ConnectionStatus` int(11) NOT NULL DEFAULT '0',
  `RackStatus` varchar(12) NOT NULL DEFAULT '',
  `TimeStamp` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00' ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bioterio_01`
--

LOCK TABLES `bioterio_01` WRITE;
/*!40000 ALTER TABLE `bioterio_01` DISABLE KEYS */;
INSERT INTO `bioterio_01` VALUES (2,'b01R01',9,0,'UNKNOWN','2016-01-30 00:59:05');
/*!40000 ALTER TABLE `bioterio_01` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping events for database 'arduinodb'
--

--
-- Dumping routines for database 'arduinodb'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-02-03  9:44:39
