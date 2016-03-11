CREATE DATABASE  IF NOT EXISTS `sg` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `sg`;
-- MySQL dump 10.13  Distrib 5.6.24, for Win64 (x86_64)
--
-- Host: 89.163.208.5    Database: sg
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

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
  `Name` varchar(40) NOT NULL,
  `Rank` varchar(10) NOT NULL DEFAULT 'U',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `Level` int(11) NOT NULL,
  `XP` float NOT NULL,
  `License` int(11) NOT NULL,
  `Rupees` int(11) NOT NULL,
  `Coins` int(11) NOT NULL,
  `Questpoints` int(11) NOT NULL,
  `ClanID` int(11) NOT NULL,
  `CharType` int(11) NOT NULL,
  `LastDailyCoins` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `age` int(2) NOT NULL,
  `zoneid` int(10) NOT NULL,
  `zoneinfo` varchar(140) NOT NULL,
  `bio` varchar(150) NOT NULL DEFAULT 'hello (:',
  PRIMARY KEY (`id`) USING BTREE,
  KEY `ID` (`id`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

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
-- Dumping events for database 'sg'
--

--
-- Dumping routines for database 'sg'
--
/*!50003 DROP PROCEDURE IF EXISTS `CreateAccount` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = latin1 */ ;
/*!50003 SET character_set_results = latin1 */ ;
/*!50003 SET collation_connection  = latin1_swedish_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = '' */ ;
DELIMITER ;;
CREATE DEFINER=`clickbait`@`%` PROCEDURE `CreateAccount`(
	IN usr varchar(20),
	IN pwd varchar(32),
	IN mail varchar(50)
)
BEGIN
INSERT INTO Accounts(
username,
password,
email
)
VALUES(
usr,
md5(pwd),
mail
);
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-03-11 18:23:21
