import sys
import re
import os
#import inspect

__PROGRAM_NAME__ = "PROGRAM NAME: POLARIS TO FUSION CONVERTER"
__AUTHOR__ = "AUTHOR: Roger Logan, LTXCredence Apps Engineer, Houston, TX"
__DATEMODIFIED__ = "LAST MODIFIED: January 19, 2009"
__VERSION__ = "VERSION: 2.0"
__FILENAME__ = "pol2fus.py"
__INPUT_FILENAME__ = "<device.[p|evo]>"
__OUTPUT_FILENAME__ = "<device.[p|evo]>.new"
__DESCRIPTION__ = """DESCRIPTION: Creates """+__OUTPUT_FILENAME__+""" from """+__INPUT_FILENAME__+"""\n\
  POLARIS TO FUSION: Converts a SINGLE SITE Mega 1 or Polaris Devicetable for use on an HF or EX tester\n\
    through the use of an HF adapter (and tower for EX) or through the use of a Polaris to EX native\n\
    board that can fit the 256PIN(round) or 376PIN(split) design.\n\
  FUSION TO FUSION:  Converts any ONE HF Fusion AdapterBoard OBJECT to an EX (and vice versa)\n\
    Can support MULTISITE, but currently only identifies CPS and HCOVI supplies."""
__INSTRUCTIONS__ = """INSTRUCTIONS: Remove ALL BUT ONE DeviceTable or AdapterBoard object from """+__INPUT_FILENAME__+""" file.\n\
  When converting a Mega 1/Polaris DeviceTable to Fusion (POL2FUS), this script\n\
  is looking for ALL occurances of the following KEYWORDS:\n\
  (devicetablename,PinSet,PinSetPP,PinSetMP,PinSetMux,PinSetMuxMP,PinSetMuxPP,PinSetSupply)\n\
  If any of these keywords are embedded in names of unwanted objects, DELETE them.\n\
  Make sure all pins exist EACH ON ONE LINE ONLY (otherwise it will be omitted).\n\
  For Fusion to Fusion conversion (FUS2FUS) this script is only looking for the \n\
  following syntax: 'TesterCh[#] = ###;' and then replaces ### with the converted value (if known).\n\
  All other information is preserved and written to """+__OUTPUT_FILENAME__+"""\n\
  After creation of """+__OUTPUT_FILENAME__+""", check all PinTypes and Power\n\
  Supplies to make sure they are correct."""

__EVO_HEADER__ = "enVision:\"bl8:R11.1.0.WW1111:S3.5\"; /* 5.7 */\n\n"
__MAXSUPPLIES__ = 16
__DEBUG__ = False
__VERBOSE__ = True

#global variables to be set by getUserInput()
__convtype__ = ""
__intype__ = ""
__outtype__ = ""
__stripcomments__ = True

#global process variables
__chanfound__ = 0
__muxchanfound__ = 0
__suppfound__ = 0
__channotfound__ = 0

class TextException(Exception): pass

class Converter(object):
  def __init__ (self,intype):
    self.intype = intype
    try:
      if intype not in ('M1','P256','P376','HF','EXT','EX256N','EX376N'):
        raise TextException()
    except Exception:
      print "Argument passed must be one of the following: 'M1', 'P256', 'P376', 'HF', 'EXT','EX256N','EX376N'"

    #WARNING: VALUES OVER 10000 ARE DUMMY VALUES
    # ( Mega1, P256, HF, EX256N )
    self.M1P256Map = [(177,233,0,316),(178,234,1,338),(137,103,2,317),(138,104,3,339),(55,39,4,68),
      (56,40,5,74),(95,35,6,67),(96,36,7,73),(57,99,8,344),(58,100,9,350),(17,97,10,345),
      (18,98,11,351),(247,171,12,66),(248,172,13,36),(215,175,14,37),(216,176,15,43),
      (97,41,16,343),(98,42,17,349),(219,235,18,312),(220,236,19,318),(217,237,20,315),
      (218,238,21,337),(99,43,22,340),(100,44,23,346),(19,45,24,342),(20,46,25,348),
      (179,239,26,313),(180,240,27,319),(139,101,28,314),(140,102,29,336),(59,47,30,341),
      (60,48,31,347),(21,49,32,297),(22,50,33,303),(143,111,34,330),(144,112,35,288),
      (23,55,36,294),(24,56,37,300),(221,181,38,331),(222,182,39,289),(141,105,40,333),
      (142,106,41,291),(101,109,42,295),(102,110,43,301),(181,177,44,332),(182,178,45,290),
      (61,53,46,296),(62,54,47,302),(183,183,48,329),(184,184,49,335),(185,245,50,185),
      (186,246,51,191),(63,51,52,293),(64,52,53,299),(145,113,54,186),(146,114,55,240),
      (25,57,56,248),(26,58,57,254),(103,107,58,292),(104,108,59,298),(249,241,60,255),
      (250,242,61,241),(223,179,62,328),(224,180,63,334),(187,243,64,182),(188,244,65,188),
      (225,247,66,184),(226,248,67,190),(65,61,68,247),(66,62,69,253),(105,117,70,246),
      (106,118,71,252),(107,115,72,243),(108,116,73,249),(67,59,74,244),(68,60,75,250),
      (27,63,76,245),(28,64,77,251),(147,119,78,183),(148,120,79,189),(227,185,80,181),
      (228,186,81,187),(229,187,82,138),(230,188,83,144),(251,189,84,242),(252,190,85,180),
      (109,125,86,150),(110,126,87,156),(69,7,88,151),(70,8,89,157),(189,191,90,139),
      (190,192,91,145),(29,3,92,152),(30,4,93,158),(149,121,94,140),(150,122,95,146),
      (151,127,96,137),(152,128,97,143),(33,65,98,200),(34,66,99,206),(31,1,100,149),
      (32,2,101,155),(253,251,102,207),(254,252,103,193),(231,253,104,135),(232,254,105,141),
      (111,123,106,147),(112,124,107,153),(191,249,108,136),(192,250,109,142),(71,5,110,148),
      (72,6,111,154),(153,129,112,234),(154,130,113,192),(195,197,114,230),(196,198,115,236),
      (155,135,116,231),(156,136,117,237),(233,193,118,232),(234,194,119,238),(73,69,120,199),
      (74,70,121,205),(35,71,122,197),(36,72,123,203),(193,255,124,233),(194,256,125,239),
      (113,133,126,198),(114,134,127,204),(235,199,128,229),(236,200,129,235),(197,201,130,412),
      (198,202,131,434),(75,67,132,196),(76,68,133,202),(77,13,134,440),(78,14,135,446),
      (115,131,136,195),(116,132,137,201),(37,9,138,441),(38,10,139,447),(255,195,140,194),
      (256,196,141,228),(157,137,142,413),(158,138,143,435),(237,205,144,411),(238,206,145,433),
      (239,203,146,408),(240,204,147,414),(117,141,148,439),(118,142,149,445),(119,139,150,436),
      (120,140,151,442),(159,143,152,410),(160,144,153,432),(199,207,154,409),(200,208,155,415),
      (79,11,156,437),(80,12,157,443),(39,15,158,438),(40,16,159,444),(1,73,160,457),
      (2,74,161,463),(123,149,162,490),(124,150,163,448),(121,145,164,493),(122,146,165,451),
      (3,75,166,454),(4,76,167,460),(41,77,168,456),(42,78,169,462),(201,213,170,491),
      (202,214,171,449),(81,79,172,455),(82,80,173,461),(161,209,174,492),(162,210,175,450),
      (163,215,176,489),(164,216,177,495),(165,221,178,57),(166,222,179,63),(43,17,180,453),
      (44,18,181,459),(125,151,182,58),(126,152,183,80),(5,23,184,88),(6,24,185,94),
      (83,21,186,452),(84,22,187,458),(241,217,188,95),(242,218,189,81),(203,211,190,488),
      (204,212,191,494),(167,219,192,54),(168,220,193,60),(205,223,194,56),(206,224,195,62),
      (45,19,196,87),(46,20,197,93),(85,81,198,86),(86,82,199,92),(47,87,200,84),
      (48,88,201,90),(7,85,202,85),(8,86,203,91),(87,83,204,83),(88,84,205,89),
      (127,147,206,55),(128,148,207,61),(209,163,208,11),(210,164,209,17),(207,161,210,53),
      (208,162,211,59),(89,31,212,23),(90,32,213,29),(243,165,214,82),(244,166,215,52),
      (169,167,216,12),(170,168,217,18),(9,25,218,25),(10,26,219,31),(49,29,220,24),
      (50,30,221,30),(129,153,222,13),(130,154,223,19),(131,157,224,10),(132,158,225,16),
      (13,95,226,72),(14,96,227,78),(11,27,228,22),(12,28,229,28),(245,231,230,79),
      (246,232,231,65),(211,229,232,8),(212,230,233,14),(171,225,234,9),(172,226,235,15),
      (91,93,236,20),(92,94,237,26),(51,89,238,21),(52,90,239,27),(175,173,240,38),
      (176,174,241,44),(135,155,242,39),(136,156,243,45),(15,37,244,69),(16,38,245,75),
      (213,169,246,40),(214,170,247,46),(93,33,248,70),(94,34,249,76),(173,227,250,41),
      (174,228,251,47),(133,159,252,42),(134,160,253,64),(53,91,254,71),(54,92,255,77)]
      
    #WARNING: VALUES OVER 10000 ARE DUMMY VALUES
    # ( P376, HF, EX376N )
    self.P376Map = [(45,0,45),(46,1,46),(47,2,47),(48,3,48),(41,4,41),(42,5,42),(101,6,101),
      (102,7,102),(43,8,43),(44,9,44),(167,10,167),(168,11,168),(227,12,227),(228,13,228),
      (165,14,165),(166,15,166),(107,16,107),(108,17,108),(105,18,105),(106,19,106),(109,20,109),
      (110,21,110),(169,22,169),(170,23,170),(111,24,111),(112,25,112),(173,26,173),(174,27,174),
      (175,28,175),(176,29,176),(171,30,171),(172,31,172),(97,32,97),(98,33,98),(237,34,237),
      (238,35,238),(235,36,235),(236,37,236),(239,38,239),(240,39,240),(39,40,39),(40,41,40),
      (37,42,37),(38,43,38),(233,44,233),(234,45,234),(249,46,249),(250,47,250),(49,48,49),
      (50,49,50),(55,50,55),(56,51,56),(53,52,53),(54,53,54),(51,54,51),(52,55,52),
      (179,56,179),(180,57,180),(117,58,117),(118,59,118),(119,60,119),(120,61,120),(113,62,113),
      (114,63,114),(247,64,247),(248,65,248),(245,66,245),(246,67,246),(241,68,241),(242,69,242),
      (243,70,243),(244,71,244),(63,72,63),(64,73,64),(61,74,61),(62,75,62),(125,76,125),
      (126,77,126),(127,78,127),(128,79,128),(177,80,177),(178,81,178),(183,82,183),(184,83,184),
      (181,84,181),(182,85,182),(59,86,59),(60,87,60),(123,88,123),(124,89,124),(115,90,115),
      (116,91,116),(121,92,121),(122,93,122),(187,94,187),(188,95,188),(57,96,57),(58,97,58),
      (7,98,7),(8,99,8),(185,100,185),(186,101,186),(189,102,189),(190,103,190),(191,104,191),
      (192,105,192),(253,106,253),(254,107,254),(255,108,255),(256,109,256),(251,110,251),
      (252,111,252),(133,112,133),(134,113,134),(129,114,129),(130,115,130),(135,116,135),
      (136,117,136),(65,118,65),(66,119,66),(67,120,67),(68,121,68),(5,122,5),
      (6,123,6),(1,124,1),(2,125,2),(3,126,3),(4,127,4),(9,128,9),(10,129,10),
      (195,130,195),(196,131,196),(193,132,193),(194,133,194),(199,134,199),(200,135,200),
      (197,136,197),(198,137,198),(131,138,131),(132,139,132),(71,140,71),(72,141,72),
      (69,142,69),(70,143,70),(13,144,13),(14,145,14),(11,146,11),(12,147,12),
      (15,148,15),(16,149,16),(137,150,137),(138,151,138),(77,152,77),(78,153,78),
      (79,154,79),(80,155,80),(75,156,75),(76,157,76),(73,158,73),(74,159,74),
      (143,160,143),(144,161,144),(139,162,139),(140,163,140),(205,164,205),(206,165,206),
      (207,166,207),(208,167,208),(141,168,141),(142,169,142),(19,170,19),(20,171,20),
      (201,172,201),(202,173,202),(203,174,203),(204,175,204),(17,176,17),(18,177,18),
      (23,178,23),(24,179,24),(147,180,147),(148,181,148),(87,182,87),(88,183,88),
      (215,184,215),(216,185,216),(145,186,145),(146,187,146),(209,188,209),(210,189,210),
      (213,190,213),(214,191,214),(151,192,151),(152,193,152),(31,194,31),(32,195,32),
      (29,196,29),(30,197,30),(27,198,27),(28,199,28),(25,200,25),(26,201,26),
      (93,202,93),(94,203,94),(159,204,159),(160,205,160),(221,206,221),(222,207,222),
      (89,208,89),(90,209,90),(91,210,91),(92,211,92),(155,212,155),(156,213,156),
      (95,214,95),(96,215,96),(153,216,153),(154,217,154),(217,218,217),(218,219,218),
      (211,220,211),(212,221,212),(149,222,149),(150,223,150),(157,224,157),(158,225,158),
      (219,226,219),(220,227,220),(223,228,223),(224,229,224),(83,230,83),(84,231,84),
      (33,232,33),(34,233,34),(85,234,85),(86,235,86),(81,236,81),(82,237,82),
      (21,238,21),(22,239,22),(231,240,231),(232,241,232),(225,242,225),(226,243,226),
      (229,244,229),(230,245,230),(163,246,163),(164,247,164),(161,248,161),(162,249,162),
      (99,250,99),(100,251,100),(103,252,103),(104,253,104),(35,254,35),(36,255,36),
      (295,256,295),(296,257,296),(291,258,291),(292,259,292),(355,260,355),(356,261,356),
      (359,262,359),(360,263,360),(357,264,357),(358,265,358),(293,266,293),(294,267,294),
      (353,268,353),(354,269,354),(289,270,289),(290,271,290),(347,272,347),(348,273,348),
      (299,274,299),(300,275,300),(303,276,303),(304,277,304),(301,278,301),(302,279,302),
      (365,280,365),(366,281,366),(367,282,367),(368,283,368),(297,284,297),(298,285,298),
      (349,286,349),(350,287,350),(363,288,363),(364,289,364),(361,290,361),(362,291,362),
      (351,292,351),(352,293,352),(345,294,345),(346,295,346),(343,296,343),(344,297,344),
      (315,298,315),(316,299,316),(313,300,313),(314,301,314),(317,302,317),(318,303,318),
      (371,304,371),(372,305,372),(309,306,309),(310,307,310),(305,308,305),(306,309,306),
      (307,310,307),(308,311,308),(311,312,311),(312,313,312),(375,314,375),(376,315,376),
      (373,316,373),(374,317,374),(319,318,319),(320,319,320),(369,320,369),(370,321,370),
      (337,322,337),(338,323,338),(341,324,341),(342,325,342),(281,326,281),(282,327,282),
      (287,328,287),(288,329,288),(339,330,339),(340,331,340),(283,332,283),(284,333,284),
      (285,334,285),(286,335,286),(269,336,269),(270,337,270),(331,338,331),(332,339,332),
      (333,340,333),(334,341,334),(329,342,329),(330,343,330),(273,344,273),(274,345,274),
      (277,346,277),(278,347,278),(275,348,275),(276,349,276),(279,350,279),(280,351,280),
      (323,352,323),(324,353,324),(257,354,257),(258,355,258),(325,356,325),(326,357,326),
      (321,358,321),(322,359,322),(267,360,267),(268,361,268),(335,362,335),(336,363,336),
      (271,364,271),(272,365,272),(265,366,265),(266,367,266),(263,368,263),(264,369,264),
      (261,370,261),(262,371,262),(327,372,327),(328,373,328),(259,374,259),(260,375,260)]

    
    # ( CPS, HCOVI, Ganged-not-used )
    self.CPStoHCOVImap = [(1,9,10),(2,137,0),(3,15,16),(4,143,0),(5,73,74),(6,142,0),(7,79,80),(8,144,0),(9,77,78),(10,139,0),(11,75,76),
      (12,141,0),(13,13,14),(14,140,0),(15,11,12),(16,138,0)]
    self.PSUPtoHCOVImap = [(1,9,10),(2,13,14),(3,73,74),(4,77,78),(5,137,138),(6,139,140),(7,141,142),(8,143,144),(9,0,0),(10,0,0),(11,0,0),
      (12,0,0),(13,0,0),(14,0,0),(15,0,0),(16,0,0)]
      
    # ( HF, EXT )
    self.HFtoEXTmap = [(0,368),(1,369),(2,370),(3,371),(4,372),(5,373),(6,374),(7,375),(8,376),(9,377),(10,378),(11,379),(12,380),(13,381),(14,382),(15,383),
      (16,304),(17,305),(18,306),(19,307),(20,308),(21,309),(22,310),(23,311),(24,312),(25,313),(26,314),(27,315),(28,316),(29,317),(30,318),(31,319),
      (32,256),(33,257),(34,258),(35,259),(36,260),(37,261),(38,262),(39,263),(40,264),(41,265),(42,266),(43,267),(44,268),(45,269),(46,270),(47,271),
      (48,320),(49,321),(50,322),(51,323),(52,324),(53,325),(54,326),(55,327),(56,328),(57,329),(58,330),(59,331),(60,332),(61,333),(62,334),(63,335),
      (64,240),(65,241),(66,242),(67,243),(68,244),(69,245),(70,246),(71,247),(72,248),(73,249),(74,250),(75,251),(76,252),(77,253),(78,254),(79,255),
      (80,176),(81,177),(82,178),(83,179),(84,180),(85,181),(86,182),(87,183),(88,184),(89,185),(90,186),(91,187),(92,188),(93,189),(94,190),(95,191),
      (96,128),(97,129),(98,130),(99,131),(100,132),(101,133),(102,134),(103,135),(104,136),(105,137),(106,138),(107,139),(108,140),(109,141),(110,142),
      (111,143),(112,192),(113,193),(114,194),(115,195),(116,196),(117,197),(118,198),(119,199),(120,200),(121,201),(122,202),(123,203),(124,204),
      (125,205),(126,206),(127,207),(128,496),(129,497),(130,498),(131,499),(132,500),(133,501),(134,502),(135,503),(136,504),(137,505),(138,506),
      (139,507),(140,508),(141,509),(142,510),(143,511),(144,432),(145,433),(146,434),(147,435),(148,436),(149,437),(150,438),(151,439),(152,440),
      (153,441),(154,442),(155,443),(156,444),(157,445),(158,446),(159,447),(160,384),(161,385),(162,386),(163,387),(164,388),(165,389),(166,390),
      (167,391),(168,392),(169,393),(170,394),(171,395),(172,396),(173,397),(174,398),(175,399),(176,448),(177,449),(178,450),(179,451),(180,452),
      (181,453),(182,454),(183,455),(184,456),(185,457),(186,458),(187,459),(188,460),(189,461),(190,462),(191,463),(192,112),(193,113),(194,114),
      (195,115),(196,116),(197,117),(198,118),(199,119),(200,120),(201,121),(202,122),(203,123),(204,124),(205,125),(206,126),(207,127),(208,48),
      (209,49),(210,50),(211,51),(212,52),(213,53),(214,54),(215,55),(216,56),(217,57),(218,58),(219,59),(220,60),(221,61),(222,62),(223,63),
      (224,0),(225,1),(226,2),(227,3),(228,4),(229,5),(230,6),(231,7),(232,8),(233,9),(234,10),(235,11),(236,12),(237,13),(238,14),(239,15),
      (240,64),(241,65),(242,66),(243,67),(244,68),(245,69),(246,70),(247,71),(248,72),(249,73),(250,74),(251,75),(252,76),(253,77),(254,78),(255,79),
      (256,336),(257,337),(258,338),(259,339),(260,340),(261,341),(262,342),(263,343),(264,344),(265,345),(266,346),(267,347),(268,348),(269,349),
      (270,350),(271,351),(272,272),(273,273),(274,274),(275,275),(276,276),(277,277),(278,278),(279,279),(280,280),(281,281),(282,282),(283,283),
      (284,284),(285,285),(286,286),(287,287),(288,288),(289,289),(290,290),(291,291),(292,292),(293,293),(294,294),(295,295),(296,296),(297,297),
      (298,298),(299,299),(300,300),(301,301),(302,302),(303,303),(304,352),(305,353),(306,354),(307,355),(308,356),(309,357),(310,358),(311,359),
      (312,360),(313,361),(314,362),(315,363),(316,364),(317,365),(318,366),(319,367),(320,208),(321,209),(322,210),(323,211),(324,212),(325,213),
      (326,214),(327,215),(328,216),(329,217),(330,218),(331,219),(332,220),(333,221),(334,222),(335,223),(336,144),(337,145),(338,146),(339,147),
      (340,148),(341,149),(342,150),(343,151),(344,152),(345,153),(346,154),(347,155),(348,156),(349,157),(350,158),(351,159),(352,160),(353,161),
      (354,162),(355,163),(356,164),(357,165),(358,166),(359,167),(360,168),(361,169),(362,170),(363,171),(364,172),(365,173),(366,174),(367,175),
      (368,224),(369,225),(370,226),(371,227),(372,228),(373,229),(374,230),(375,231),(376,232),(377,233),(378,234),(379,235),(380,236),(381,237),
      (382,238),(383,239),(384,464),(385,465),(386,466),(387,467),(388,468),(389,469),(390,470),(391,471),(392,472),(393,473),(394,474),(395,475),
      (396,476),(397,477),(398,478),(399,479),(400,400),(401,401),(402,402),(403,403),(404,404),(405,405),(406,406),(407,407),(408,408),(409,409),
      (410,410),(411,411),(412,412),(413,413),(414,414),(415,415),(416,416),(417,417),(418,418),(419,419),(420,420),(421,421),(422,422),(423,423),
      (424,424),(425,425),(426,426),(427,427),(428,428),(429,429),(430,430),(431,431),(432,480),(433,481),(434,482),(435,483),(436,484),(437,485),
      (438,486),(439,487),(440,488),(441,489),(442,490),(443,491),(444,492),(445,493),(446,494),(447,495),(448,80),(449,81),(450,82),(451,83),
      (452,84),(453,85),(454,86),(455,87),(456,88),(457,89),(458,90),(459,91),(460,92),(461,93),(462,94),(463,95),(464,16),(465,17),(466,18),
      (467,19),(468,20),(469,21),(470,22),(471,23),(472,24),(473,25),(474,26),(475,27),(476,28),(477,29),(478,30),(479,31),(480,32),(481,33),
      (482,34),(483,35),(484,36),(485,37),(486,38),(487,39),(488,40),(489,41),(490,42),(491,43),(492,44),(493,45),(494,46),(495,47),(496,96),
      (497,97),(498,98),(499,99),(500,100),(501,101),(502,102),(503,103),(504,104),(505,105),(506,106),(507,107),(508,108),(509,109),(510,110),(511,111)]
      
  #End __init__ ()
  #-----------------------------------------------------------------------
  #   getHForEXT
  #-----------------------------------------------------------------------
  def getHForEXT(self,inCHAN,get):
    inCHAN=int(inCHAN)
    outCHAN=-1
    for hf,ext in iter(self.HFtoEXTmap):
      if get=='EXT' and inCHAN==hf:
        outCHAN=ext;break
      elif get=='HF' and inCHAN==ext:
        outCHAN=hf;break
    if __DEBUG__:print 'getHForEXT()\nget:',get,'\ninCHAN:',inCHAN,'\noutCHAN:',outCHAN,'\n\n'
    if outCHAN>=0:return str(outCHAN)
    else:
      print "ERROR!!! "+get+" Channel for '"+str(inCHAN)+"' not found - INSERTING 999999"
      return str(999999)
    #End if
  #End getHForEXT()
  #-----------------------------------------------------------------------
  #   getOVIorCPS
  #-----------------------------------------------------------------------
  def getOVIorCPS(self,inSupply,get='HCOVI'):
    inSupply=int(inSupply)
    outSupply=-1
    for cps,hcovi,gang in iter(self.CPStoHCOVImap):
      if get=='HCOVI' and inSupply==cps:
        outSupply=hcovi;break
      elif get=='CPS' and inSupply==hcovi:
        outSupply=cps;break
    if outSupply>=0:return str(outSupply)
    else:
      print "ERROR!!! "+__outtype__+" Supply for '[CPS|HCOVI]"+str(inSupply)+"' not found - INSERTING 999999"
      return str(999999)
    #End if
  #End getOVIorCPS()
  #-----------------------------------------------------------------------
  #   getPOL2HCOVI
  #-----------------------------------------------------------------------
  def getPOL2HCOVI(self,inSupply,get='HCOVI'):
    inSupply=int(inSupply)
    outSupply=-1
    for cps,hcovi,gang in iter(self.PSUPtoHCOVImap):
      if get=='HCOVI' and inSupply==cps:
        outSupply=hcovi;break
      elif get=='CPS' and inSupply==hcovi:
        outSupply=cps;break
    if outSupply>=0:return str(outSupply)
    else:
      print "ERROR!!! "+__outtype__+" Supply for '[CPS|HCOVI]"+str(inSupply)+"' not found - INSERTING 999999"
      return str(999999)
    #End if
  #End getOVIorCPS()
  #-----------------------------------------------------------------------
  #   getChan
  #-----------------------------------------------------------------------
  def getChan(self,inCHAN):
    inCHAN=int(inCHAN)
    outCHAN=-1
    error=False
    
    if __convtype__ == 'POL2FUS':
  
      if __intype__ in ('M1','P256'):
        if __DEBUG__:print lineno()
        for m1,po,hf,exnatv in iter(self.M1P256Map):
          if __intype__=='M1' and inCHAN==m1:
            if __outtype__=='HF':outCHAN = hf;break
            elif __outtype__ == 'EX256N':outCHAN = exnatv;break
            else:outCHAN = self.getHForEXT(hf,'EXT') # get EXT channel
          elif __intype__=='P256' and inCHAN==po:
            if __outtype__=='HF':outCHAN = hf;break
            elif __outtype__ == 'EX256N':outCHAN = exnatv;break
            else:outCHAN = self.getHForEXT(hf,'EXT') # get EX channel
      elif __intype__ =='P376':
        if __DEBUG__:print lineno()
        for ps,hf,exnatv in iter(self.P376Map):
          if inCHAN==ps:
            if __outtype__=='HF':outCHAN = hf;break
            elif __outtype__ == 'EX376N':outCHAN = exnatv;break
            else:outCHAN = self.getHForEXT(hf,'EXT') # get EX channel
      else:
        #unknown __intype__
        error=True
      #End if
  
    elif __convtype__ == 'FUS2FUS':
      
      if 'EX256N' in (__intype__,__outtype__):
        if __DEBUG__:print lineno()
        for m1,po,hf,exnatv in iter(self.M1P256Map):
          if __intype__ == 'HF' and inCHAN==hf:outCHAN=exnatv;break
          elif __intype__ == 'EX256N' and inCHAN==exnatv:outCHAN=hf;break
          else: error=True
          #End if
      elif 'EX376N' in (__intype__,__outtype__):
        if __DEBUG__:print lineno()
        for ps,hf,exnatv in iter(self.P376Map):
          if __intype__ == 'HF' and inCHAN==hf:outCHAN=exnatv;break
          elif __intype__ == 'EX256N' and inCHAN==exnatv:outCHAN=hf;break
          else: error=True
          #End if
      elif 'EXT' in (__intype__,__outtype__):
        if __DEBUG__:print lineno()
        if __intype__ == 'HF':outCHAN = self.getHForEXT(inCHAN,'EXT')
        elif __intype__ == 'EXT':outCHAN = self.getHForEXT(inCHAN,'HF')
        else:error=True
        #End if
  
    else:
      #unknown __convtype__
      error=True
    #End if

    if __DEBUG__:print 'getChan()\ninCHAN:',inCHAN,'\noutCHAN:',outCHAN,'\n\n'
    
    if outCHAN>=0 and not error:
      return str(outCHAN)
    else:
      print "ERROR!!! "+__outtype__+" Channel for '"+str(inCHAN)+"' not found - INSERTING 999999"
      return str(999999)
    #End if
  #End getChan()
#End Converter()
#-----------------------------------------------------------------------
#   lineno
#-----------------------------------------------------------------------
def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
#-----------------------------------------------------------------------
#   printpins
#-----------------------------------------------------------------------
def printpins (outfile,pins,mux=False):
  global __chanfound__
  global __muxchanfound__
  conv=Converter(__intype__)
  for pin in pins:
    __chanfound__+=1
    pin=pin.replace(' ','')
    p=pin.split(',')
    pinname=p[0]
    ppid=p[1]
    if not mux and len(p)!=8 or mux and len(p)!=9:
      print 'PARSE ERROR!!! (SKIPPING):',','.join(p)
      continue
    try:
      checkifvalid = str(int(strip(p[2],'{','}')))
      if mux:
        checkifvalid = str(int(strip(p[3],'{','}')))
    except Exception:
      print 'PARSE ERROR!!! (SKIPPING):',','.join(p)
      continue
    pkgpin = re.search("{(?P<pkgpinid>.*)}",p[2]) # create backreference
    pkgpinid=''
    if pkgpin:
      pkgpinid=':'+pkgpin.group('pkgpinid') # get backreference
      p[2]=p[2].replace(pkgpin.group(),'')
    #End if
    chan=conv.getChan(p[2])
    if mux:pintype=p[4]
    else:pintype=p[3]
    #End if
    comments = re.search("{(.*)}",pintype)
    if comments:#Remove comments
      pintype=pintype.replace(comments.group(),'')
    pintype=pintype.replace(' ','')
    outfile.write('    Pin { Name = %-12s Ppid = \"%-10s' % (pinname+';',ppid+pkgpinid+'\";'))
    outfile.write(' XCoord = (999,999); PinType = %-5s' % (pintype+';'))
    outfile.write(' Connection[0] { TesterCh[1] = %-5s } }\n' % (chan+';'))
    if mux:
      __muxchanfound__+=1
      muxpin=conv.getChan(p[3])
      outfile.write('    Pin { Name = %-12s Ppid = \"%-10s' % (pinname+'m;',ppid+pkgpinid+'\";'))
      outfile.write(' XCoord = (999,999); PinType = %-5s' % (pintype+';'))
      outfile.write(' Connection[0] { TesterCh[1] = %-5s } }\n' % (muxpin+';'))
      print "MUXPIN ADDED: "+pinname+"m"
    #End if
  #End for
#End printpins ()
#-----------------------------------------------------------------------
#   printsupplies
#-----------------------------------------------------------------------
def printsupplies (outfile,supplies):
  global __suppfound__
  conv=Converter(__intype__)
  for supply in supplies:
    __suppfound__+=1
    supply=supply.replace(' ','')
    comments = re.search("{(.*)}",supply)
    if comments:#Remove comments
      supply=supply.replace(comments.group(),'')
    s=supply.split(',')
    if len(s)!=7:
      print 'PARSE ERROR!!! (SKIPPING):',','.join(s)
      continue
    sname=s[0]
    ppid=s[1]
    s_num = re.search("Supply(?P<s_num>.*)",s[2])
    if s_num:
      try:
        if not len(s_num.group('s_num')) or int(s_num.group('s_num')) not in range(1,__MAXSUPPLIES__):
          raise TextException()
        else:
          pintype = sname+'PWR'
          if __outtype__=='EXT':
            newsupply = 'HCOVI'+conv.getOVIorCPS(s_num.group('s_num'))
          elif __outtype__=='EX256N':
            newsupply = 'HCOVI'+conv.getPOL2HCOVI(s_num.group('s_num'))
          elif __outtype__=='EX376N':
            newsupply = 'HCOVI'+conv.getPOL2HCOVI(s_num.group('s_num'))
          else:
            newsupply = 'CPS'+s_num.group('s_num')
      except Exception:
        badsupply='Supply'+s_num.group('s_num')
        print "ERROR!!! "+__outtype__+" Supply for '"+badsupply+"' not found - INSERTING 999999"
        pintype = 'UNKNOWN'
        newsupply = '999999'
      #End if
    else:
      pintype = sname+'GND_'
      newsupply = 'GND'
    outfile.write('    Pin { Name = %-12s Ppid = \"%-10s' % (sname+';',ppid+'\";'))
    outfile.write(' XCoord = (999,999); PinType = %-10s' % (pintype+';'))
    outfile.write(' Connection[0] { TesterCh[1] = %-5s } }\n' % (newsupply+';'))
#End printsupplies ()
#-----------------------------------------------------------------------
#   promptUser()
#-----------------------------------------------------------------------
def promptUser(query,errmsg,choices):
  exit=False
  while 1:
    try:
      ans = raw_input(query)
      if ans.lower()=='x':
        exit=True
        break
      elif ans.lower() not in choices:
        raise TextException()
      else:
        break
    except Exception:
      print errmsg
  #End while
  if exit:sys.exit(-1)
  else: return ans

#-----------------------------------------------------------------------
#   getUserInput
#-----------------------------------------------------------------------
def getUserInput():
  #global reference so these variables can be edited in this function
  global __convtype__
  global __intype__
  global __outtype__
  global __stripcomments__

  #local vars
  convtype_errmsg = "\nERROR!!! You Must Choose 'a' or 'b' (or 'x' to abort)\n"
  convtype_q = """Enter type of Conversion:\n\
    a) POLARIS TO FUSION (M1,POL ==> HF,EX)\n\
    b) FUSION TO FUSION (HF <==> EX)\n"""
  convtype_choices = ('a','b')
  #--------------------------------
  intype_errmsg1 = "\nERROR!!! You Must Choose 'a','b', or 'c' (or 'x' to abort)\n"
  intype_q1 = """Enter File Type for INPUT (a,b,or c):\n\
    a) Mega1 (256 PIN)\n\
    b) Polaris (256 PIN)\n\
    c) Polaris (376 PIN)\n"""
  intype_choices1 = ('a','b','c')
  #--------------------------------
  intype_errmsg2 = "\nERROR!!! You Must Choose 'a','b','c', or 'd' (or 'x' to abort)\n"
  intype_q2 = """Enter File Type for INPUT (a,b,c, or d):\n\
    a) HF\n\
    b) EX with HF TOWER (EXT)                --OUTPUT FILE: 'HF'\n\
    c) EX M1/Polaris 256 pin NATIVE (EX256N) --OUTPUT FILE: 'HF'\n\
    d) EX Polaris 376 pin NATIVE (EX376N)    --OUTPUT FILE: 'HF'\n"""
  intype_choices2 = ('a','b','c','d')
  #--------------------------------
  outtype_errmsg1 = "\nERROR!!! You Must Choose 'a','b', or 'c' (or 'x' to abort)\n"
  outtype_q1 = """Enter File Type for OUTPUT (a,b, or c):\n\
    a) HF \n\
    b) EX with HF TOWER (EXT)\n\
    c) EX Polaris NATIVE (EX256N / EX376N)\n"""
  outtype_choices1 = ('a','b','c')
  #--------------------------------
  outtype_errmsg2 = "\nERROR!!! You Must Choose 'a','b', or 'c' (or 'x' to abort)\n"
  outtype_q2 = """Enter File Type for OUTPUT (a,b,or c):\n\
    a) EX with HF TOWER (EXT)\n\
    b) EX 256 pin NATIVE for M1 or Polaris  (EX256N)\n\
    c) EX 376 pin NATIVE for Polaris (EX376N)\n"""
  outtype_choices2 = ('a','b','c')
  #--------------------------------
  stripcom_errmsg = "\nERROR!!! You Must Choose 'y' or 'n' (or 'x' to abort)\n"
  stripcom_q = "Strip ALL comments before processing? (y or n)\n"
  stripcom_choices = ('y','n')
  
  convtype = promptUser(convtype_q,convtype_errmsg,convtype_choices)
  if convtype.lower()=='a':
    __convtype__ = 'POL2FUS';
  
    #INPUT FILE INFO
    intype = promptUser(intype_q1,intype_errmsg1,intype_choices1)
    if intype.lower()=='a': __intype__ = 'M1'
    elif intype.lower()=='b': __intype__ = 'P256'
    elif intype.lower()=='c': __intype__ = 'P376'
    #End if
  
    #INPUT FILE INFO
    outtype = promptUser(outtype_q1,outtype_errmsg1,outtype_choices1)
    if outtype.lower()=='a': __outtype__ = 'HF'
    elif outtype.lower()=='b': __outtype__ = 'EXT'
    elif outtype.lower()=='c' and __intype__ in ('M1','P256'): __outtype__ = 'EX256N'
    else: __outtype__ = 'EX376N'
    #End if
  
  elif convtype.lower()=='b':
    __convtype__ = 'FUS2FUS';
  
    #INPUT FILE INFO
    intype = promptUser(intype_q2,intype_errmsg2,intype_choices2)
    if intype.lower()=='a':__intype__ = 'HF'
    elif intype.lower()=='b': __intype__ = 'EXT'; __outtype__ = 'HF'
    elif intype.lower()=='c': __intype__ = 'EX256N'; __outtype__ = 'HF'
    elif intype.lower()=='d': __intype__ = 'EX376N'; __outtype__ = 'HF'
    #End if
  
    #INPUT FILE INFO
    if __intype__ == 'HF':
      outtype = promptUser(outtype_q2,outtype_errmsg2,outtype_choices2)
      if outtype.lower()=='a': __outtype__ = 'EXT'
      elif outtype.lower()=='b': __outtype__ = 'EX256N'
      elif outtype.lower()=='c': __outtype__ = 'EX376N'
    else:
      __outtype__ = 'HF'
    #End if
    
  #End if
  
  strip = promptUser(stripcom_q,stripcom_errmsg,stripcom_choices)
  if strip.lower()=='n':
    __stripcomments__ = False # default is True
#End getUserInput()
#-----------------------------------------------------------------------
#   strip
#-----------------------------------------------------------------------
def strip(string,delim_st,delim_sp='\n',ignore_st=None,ignore_sp=None):
  """This will return 'string' stripped of anything between (and including) 'delim_st' and 'delim_sp'\
  (except when 'delim_sp' is newline) EVEN IF THEY ARE NESTED.  Delimiters can be any string or character\
  (alphanumerics as well as non-alphanumerics).\
  'ignore_st' and 'ignore _sp' allow removal of substrings from string before parsing for nested strings."""
  
  if ignore_st and ignore_sp:
    string=strip(string,ignore_st,ignore_sp)
  
  es_delim_st=re.escape(delim_st) # returns non-alphanumerics backslashed for regex
  es_delim_sp=re.escape(delim_sp) # returns non-alphanumerics backslashed for regex
  
  if delim_sp!='\n':
    # THIS IS A MULTILINE STRING SO WE NEED TO CHECK FOR NESTING
    patrn = re.compile(
      # This is a regex WITHIN a regex
      "("+es_delim_st+      # outer regex start
      "(?:.*?)"+                # inner regex  ?: prevents backreference of inner regex
                                #              .* searches for any char except '\n'(any # of times)
                                #              ? before closing makes this 'lazy' (it will grab FIRST occurance of 'delim_sp')
      es_delim_sp+")",      # outer regex end
      re.DOTALL|            # re.DOTALL overrides '.*' limitation of '\n' described above
      re.VERBOSE)           # re.VERBOSE allows these comments (ignores whitespace including newlines)
  else:
    # THIS IS A SINGLELINE STRING - NO NEED TO CHECK BEYOND NEWLINE
    patrn = re.compile("("+es_delim_st+"(?:.*))")
  while 1:
    strObj = patrn.search(string) # search for 1st occurance of backreferenced pattern (from outer regex defined above)
    if not strObj:break  # no more, we're done
    # found a substring
    substring=strObj.group() # get string from RE object
    if substring.count(delim_st) and delim_st!= delim_sp>1:
      if delim_sp!='\n':
        # remove nested substring (two 'delim_st' and one 'delim_sp')
        strObj = patrn.search(substring,1) # ignore 1st delim_st
      else:
        strObj = patrn.search(substring)
      if strObj:
        substring = strObj.group() # get string from RE object
    string=string.replace(substring,'',1) # only remove that one instance
  return string
#End strip()
#-----------------------------------------------------------------------
#   getAdapterName()
#-----------------------------------------------------------------------
def getAdapterName(contents):
  if __convtype__ == 'POL2FUS':
    devtblname = re.search("devicetablename(\s*):=(\s*)'(?P<name>.*)'",contents)
  elif __convtype__ == 'FUS2FUS':
    devtblname = re.search("AdapterBoard(\s*)(?P<name>.*)(\s*)\{",contents)
  else:
    if __DEBUG__: print 'LINE: ',lineno()
    print 'ERROR!!! UNKNOWN CONVERSION TYPE.\nEXITING'
    try:outfile.close();
    except Exception:pass
    try:os.remove(__OUTPUT_FILENAME__);
    except Exception:pass
    sys.exit(-1)
  #End if
  if devtblname:
    devtblname=devtblname.group('name')
    devtblname=devtblname.strip()
  else:
    devtblname="NO_TABLENAME_FOUND"
  mod='__'+__intype__+'to'+__outtype__
  devtblname+=mod
  return devtblname
  
#-----------------------------------------------------------------------
#   main
#-----------------------------------------------------------------------
def main():
  global __OUTPUT_FILENAME__
  global __chanfound__
  global __suppfound__
  global __channotfound__
  # Get the arguments from the command line, except the first one.
  args = sys.argv[1:]
  if len(args) != 1:
    print "usage: "+__FILENAME__+" "+__INPUT_FILENAME__
    sys.exit(-1)

  os.system('clear')
  if __VERBOSE__:
    print '\n\n'
    print __PROGRAM_NAME__
    print __AUTHOR__
    print __DATEMODIFIED__
    print __VERSION__
    print __DESCRIPTION__
    print __INSTRUCTIONS__
  print '\n\n'

  getUserInput()
  print '\n'

  # Open the file for read only.
  infile = file(args[0], 'r')
  __OUTPUT_FILENAME__=args[0]+'.new'
  if __DEBUG__:print '__OUTPUT_FILENAME__ : ',__OUTPUT_FILENAME__
  outfile = open(__OUTPUT_FILENAME__, "w")
  outfile.write(__EVO_HEADER__)
  contents = infile.read()
  infile.close()
  
  #get AdapterBoard name before contents are unusable
  adaptername = getAdapterName(contents)

  if __convtype__ == 'POL2FUS':
    if __stripcomments__:
      contents=strip(contents,'(*','*)')
      contents=strip(contents,'{','}')
    #End if
    
    #Remove spaces, but NOT newlines - newlines are needed for findall() used below
    ws_patrn = re.compile("([ \t\r\f\v]*)")
    contents=re.sub(ws_patrn,'',contents)
  
    # SET SEARCH PATTERNS
    # (?:[MP]P)? does not create a backreference which would break the findall() used later that is...
    # looking for (.*) which IS a backreference to regex
    pin_patrn = re.compile("PinSet(?:[MP]P)?\((.*)\)")
    muxpin_patrn = re.compile("PinSetMux(?:[MP]P)?\((.*)\)")
    supply_patrn = re.compile("PinSetSupply\((.*)\)")
  
    pins=pin_patrn.findall(contents)
    muxpins=muxpin_patrn.findall(contents)
    supplies=supply_patrn.findall(contents)
  
    outfile.write('AdapterBoard '+adaptername+' {\n')
    printpins(outfile,pins)
    printpins(outfile,muxpins,True)
    printsupplies(outfile,supplies)
    outfile.write('}\n')
    if __chanfound__ or __suppfound__:
      if  __muxchanfound__: 
        print 'CONVERTED',__chanfound__,'(+',__muxchanfound__,'mux)',__intype__,'pins to',__outtype__,'channels'
      else:
        print 'CONVERTED',__chanfound__,__intype__,'pins to',__outtype__,'channels'
      if __suppfound__:
        print 'CONVERTED',__suppfound__,__intype__,'supplies to',__outtype__,'supplies'
      contents='AdapterBoard '+adaptername+' {\n'+contents+'\n}'
    else:
      print 'NO PINS FOUND FROM INPUT FILE!!!!'
      print 'EXITING'
      try:outfile.close();
      except Exception:pass
      try:os.remove(__OUTPUT_FILENAME__);
      except Exception:pass
      sys.exit(-1)
    #End if
  
  elif __convtype__ == 'FUS2FUS':
  
    if __stripcomments__:
      contents=strip(contents,'//')
      contents=strip(contents,'/*','*/')
  
    adaptcon_patrn = re.compile("{(?P<adaptcon>.*)}",re.DOTALL)
    adaptconObj = adaptcon_patrn.search(contents)
  
    if adaptconObj:
      contents = adaptconObj.group('adaptcon')
    else:
      if __DEBUG__: print 'LINE: ',lineno()
      print 'ERROR!!! No AdapterBoard object found.\nEXITING'
      try:outfile.close();
      except Exception:pass
      try:os.remove(__OUTPUT_FILENAME__);
      except Exception:pass
      sys.exit(-1)
    #End if
    
    conv=Converter(__intype__)
    allchan_patrn = re.compile("TesterCh\[(.*)\](?:\s*)=(?:\s*)(.*);")
    allchans=allchan_patrn.findall(contents)
    
    skip=False
    for i,chan in allchans:
      chan=chan.strip()
      if __intype__ == 'HF':
        if chan.count('CPS'):
          try:
            newchan = chan.replace('CPS','')
            newchan = 'HCOVI'+conv.getOVIorCPS(newchan,'HCOVI')
            __suppfound__+=1
          except Exception:
            if __DEBUG__: print "UNKNOWN CHANNEL: \'"+chan+"\' ON LINE: ",lineno()
            skip=True #unknown channel - LEAVE ALONE
        elif chan=='GND':
          newchan=chan
          __suppfound__+=1
        elif chan.count('HCOVI'):
          print "WARNING!!! Found HCOVI in",__intype__,"INPUT FILE - INSERTING 999999"
          newchan='999999'
        else:
          try:
            checkifvalid = str(int(chan))
            newchan = conv.getChan(chan)
            __chanfound__+=1
          except Exception:
            if __DEBUG__: print "UNKNOWN CHANNEL: \'"+chan+"\' ON LINE: ",lineno()
            skip=True #unknown channel - LEAVE ALONE
        #End if
      elif __intype__ in ('EXT','EX256N','EX376N'):
        if chan.count('HCOVI'):
          try:
            newchan = chan.replace('HCOVI','')
            newchan = 'CPS'+conv.getOVIorCPS(newchan,'CPS')
            __suppfound__+=1
          except Exception:
            if __DEBUG__: print "UNKNOWN CHANNEL: \'"+chan+"\' ON LINE: ",lineno()
            skip=True #unknown channel - LEAVE ALONE
        elif chan=='GND':
          newchan=chan
          __suppfound__+=1
        elif chan.count('CPS'):
          print "WARNING!!! Found CPS in",__intype__,"INPUT FILE - INSERTING 999999"
          newchan='999999'
        else:
          try:
            checkifvalid = str(int(chan))
            newchan = conv.getChan(chan)
            __chanfound__+=1
          except Exception:
            if __DEBUG__: print "UNKNOWN CHANNEL: \'"+chan+"\' ON LINE: ",lineno()
            skip=True #unknown channel - LEAVE ALONE
        #End if
      #End if
      
      if not skip:
        newchan_patrn = re.compile("TesterCh\["+i+"\](?:\s*)=(?:\s*)("+chan+")(?:\s*);")
        found = newchan_patrn.search(contents)
        if found:
          oldstr = found.group()
          #add 'xxxxx' so we don't keep replacing values that have already been replaced
          newstr = "TesterCh["+i+"] = xxxxx"+newchan+";"
        else:
          print "ERROR!!! "+__outtype__+" Channel for '"+chan+"' not found - INSERTING 999999"
          newstr = "TesterCh["+i+"] = xxxxx999999;"
        #End if
        contents = contents.replace(oldstr,newstr)
      else:
        __channotfound__+=1
      #End if
      
    #End for
      
    #strip each instance of 'xxxxx' that was added above
    contents=contents.replace('xxxxx','')

    if __chanfound__:
      print 'CONVERTED',__chanfound__,__intype__,'channels to',__outtype__,'channels'
      if __suppfound__:
        print 'CONVERTED',__suppfound__,__intype__,'supplies to',__outtype__,'supplies'
      if __channotfound__:
        print 'SKIPPED',__channotfound__,'unknown channels'
      contents='AdapterBoard '+adaptername+' {\n'+contents+'\n}'
    else:
      print 'NO TESTER CHANNELS FOUND FROM INPUT FILE!!!!'
      print 'EXITING'
      try:outfile.close();
      except Exception:pass
      try:os.remove(__OUTPUT_FILENAME__);
      except Exception:pass
      sys.exit(-1)
    #remove xtra newlines even if separated by whitespace
    dirty_patrn = re.compile("\n(\s*)\n")
    contents=re.sub(dirty_patrn,'\n',contents)
    outfile.write(contents+'\n')

  else:

    if __DEBUG__: print 'LINE: ',lineno()
    print 'UNKNOW CONVERSION TYPE!!!\nEXITING'
    try:outfile.close();
    except Exception:pass
    try:os.remove(__OUTPUT_FILENAME__);
    except Exception:pass
    sys.exit(-1)
  
  #End if
  
  print "SUCCESS!!! NEW FILE CREATED: "+__OUTPUT_FILENAME__
  print "NEW ADAPTERBOARD NAME: "+adaptername
  outfile.close()
#End main()
#-----------------------------------------------------------------------
#   BEGIN MAIN
#-----------------------------------------------------------------------
if __name__ == '__main__':
  main()
