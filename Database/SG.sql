CREATE DATABASE  IF NOT EXISTS `sg` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `sg`;
-- MySQL dump 10.13  Distrib 5.6.24, for Win64 (x86_64)
--
-- Host: 89.163.208.5    Database: sg
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

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
-- Table structure for table `Accounts`
--

DROP TABLE IF EXISTS `Accounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Accounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(20) NOT NULL,
  `password` varchar(32) NOT NULL,
  `email` varchar(50) DEFAULT NULL,
  `register_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `verified` tinyint(4) NOT NULL DEFAULT '1',
  `banned` tinyint(4) NOT NULL DEFAULT '0',
  `Sessionkey` varchar(45) DEFAULT NULL,
  `ingamecash` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `ID` (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Accounts`
--

LOCK TABLES `Accounts` WRITE;
/*!40000 ALTER TABLE `Accounts` DISABLE KEYS */;
INSERT INTO `Accounts` VALUES (1,'admin','21232f297a57a5a743894a0e4a801fc3','some@thi.ng','2015-12-09 15:44:16',1,0,'BKX5z5hF8r686z06W3OrcnQfm05ahFCY',0),(2,'simon','21232f297a57a5a743894a0e4a801fc3','irgendwas@mail.at','2015-12-16 18:39:08',1,0,'mRv6hiezto3ohsRTHAhAPZzgQu1l55Ix',0);
/*!40000 ALTER TABLE `Accounts` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Chars`
--

DROP TABLE IF EXISTS `Chars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Chars` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(40) NOT NULL,
  `Rank` varchar(10) NOT NULL DEFAULT 'U',
  `last_login` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `Level` int(11) NOT NULL,
  `XP` double NOT NULL,
  `License` int(11) NOT NULL,
  `Rupees` int(11) NOT NULL,
  `Coins` int(11) NOT NULL,
  `Questpoints` int(11) NOT NULL,
  `ClanID` int(11) NOT NULL,
  `AccountID` int(11) DEFAULT NULL,
  `CharType` int(11) NOT NULL,
  `LastDailyCoins` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `age` int(2) DEFAULT '0',
  `zoneid` int(10) DEFAULT '0',
  `zoneinfo` varchar(140) DEFAULT NULL,
  `bio` varchar(150) DEFAULT 'hello (:',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `FK_Accounts` (`AccountID`),
  CONSTRAINT `FK_Accounts` FOREIGN KEY (`AccountID`) REFERENCES `Accounts` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Chars`
--

LOCK TABLES `Chars` WRITE;
/*!40000 ALTER TABLE `Chars` DISABLE KEYS */;
INSERT INTO `Chars` VALUES (3,'Test','3','2015-12-09 18:16:24',40,10,5,10,310,0,0,1,5,'2015-12-25 15:28:07',19,0,'NRW','Das ist ein Test'),(4,'Simon','0','2015-12-17 03:11:03',40,0,5,10,10,0,0,2,5,'2015-12-09 18:16:24',0,0,NULL,'hello (:');
/*!40000 ALTER TABLE `Chars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Friends`
--

DROP TABLE IF EXISTS `Friends`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Friends` (
  `id` int(11) NOT NULL,
  `Relation_A` int(11) NOT NULL,
  `Relation_B` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Friends`
--

LOCK TABLES `Friends` WRITE;
/*!40000 ALTER TABLE `Friends` DISABLE KEYS */;
/*!40000 ALTER TABLE `Friends` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Inventory`
--

DROP TABLE IF EXISTS `Inventory`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Inventory` (
  `id` int(11) DEFAULT NULL,
  `Equiped` tinyint(1) NOT NULL DEFAULT '1',
  `ItemID` int(11) NOT NULL,
  `CharID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Inventory`
--

LOCK TABLES `Inventory` WRITE;
/*!40000 ALTER TABLE `Inventory` DISABLE KEYS */;
/*!40000 ALTER TABLE `Inventory` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-12-25 17:33:04
