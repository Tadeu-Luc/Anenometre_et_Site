#!/usr/bin/env python

#Script de lecture et mise en cache de données Arduino dans une base Mysql.


#-----------------------Importation------------------------------------#
from __future__ import with_statement
import time
import os
import serial 
import dataset

import shutil
import datetime
import mysql.connector
import MySQLdb
#-----------------------------Variable---------------------------------#

port = "/dev/ttyACM0"                                                       #port arduino

date=''
last_data=''
last_date=date=datetime.datetime.now().strftime("%Y-%m-%d")                 #Permet la recuperation db 
date2=datetime.datetime.now().strftime("%Y-%m-%d")                 
x=0  
y=0                                                                         #Variable boucle
data=('a,a,a,a,a,a')                                                        #tableau de donnee recuperer
#db = sqlite3.connect("database.db")

db=mysql.connector.connect(host="localhost",user="Eixa@localhost",passwd="Eixa6",database="METEO")
conn=db.cursor()
text=""
#table = db['data']                                                         # database 
a='a'
b='a'
c='a'
d='a'

#----------------------------Fonction_remplissage----------------------#
#def function_table(data): 
#    if text[1]=='a' or text[1]=='':
#        text[1]=last_data[1]
#        
#    if text[2]=='a' or text[2]=='':
#        text[1]=last_data[2]
#        
#    if text[3]=='a' or text[3]=='':
#       text[3]=last_data[3]
#        
# text[4]=last_data[4]
#        
#   return (text)
#---------------------------DROP_TABLES--------------------------------#
def function_createdb():
	conn.execute("CREATE DATABASE IF NOT EXISTS METEO;")                            #Creation de la Database (si non existante)
	db.commit()
	
	
	
#---------------------------DROP_TABLES--------------------------------#
def drop_tables():
	conn.execute("DROP TABLE IF EXISTS Anemometre")
	db.commit()                                                             	#commit dans notre bdd




#---------------CREATION_TABLES----------------------------------------#
def create_tables():
	conn.execute("CREATE TABLE IF NOT EXISTS Anemometre (id INT AUTO_INCREMENT PRIMARY KEY, Vitesse VARCHAR(255), Direction VARCHAR(255), Angle VARCHAR(255), Typedetemps VARCHAR(255),Heure VARCHAR(255))")
	db.commit()                                                                     #Creation des tables (si non existantes)
	
	
	
	
	
#-----------------------Remplissage_Tables-----------------------------#
def functions_tables_def(a,b,c,d,date):
	bfn=("INSERT INTO Anemometre (Vitesse, Direction, Angle, Typedetemps, Heure) VALUES (%s, %s, %s, %s, %s)")
	val=(a,b,c,d,date)
	#print val
	conn.execute(bfn, val)
	db.commit()
	#print(conn.rowcount, "record inserted.")                                       #commit dans notre bdd

def functions_copie_db():
        #shutil.copyfile ('er.py','/home/pi/Archive/Fichier_meteo'+str(date))
        time.sleep(5)                                                                   #temps de pause de copie fichier 
        
        
        
        
#-----------------------Principal--------------------------------------#		#Boucle infini
def function_principal(last_date,date2):
																									
	data=ser.readline() 								#lecture donnees Arduino
	#print ("data_local "+data)                                                     #("data_local "+data)
	text=data.split(",")                                                            #decoupage a chaque " , " pour creer notre texte
    
	#print (data)                                                                   #affichage du tableau data
	if text[0]=='a' and text[5]=='a':
																								
		a=text[1]
		b=text[2]
		c=text[3]                                                               #Different valeurs de notre arduino en cache
		d=text[4]

		date=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")              #heure reel
		date2=datetime.datetime.now().strftime("%Y-%m-%d")                      #heure pour test fonction
		#function_table(data)
        
		#insert={'Vitesse': a, 'Direction': b, 'Angle': c,'Typedetemps': d, 'Heure': date}          #insertion dans la database des differentes tables
        
		#last_data=(data)                                                       #mise en cache pour modifie les futurs erreurs de synchronisation
		functions_tables_def(a,b,c,d,date)
		functions_copie_db()
        
        
		date2=datetime.datetime.now().strftime("%Y-%m-%d")
		
		print "reception : ",a,b,c,d,date
		if (date2)!=(last_date):
			last_date=date2
		time.sleep(60)							        #Met en pause le programme pour ne pas remplir la base de donnees a chaque appel de la fonction (environ toutes les 4 secondes sans) 
		function_principal(last_date,date2)
		
			
		                                                                      
	else:
		print "erreur synchronisation"                                          #en cas d erreur relance le programme (les erreurs sont du a la synchronisation).
		function_principal(last_date,date2)
    
    
#-----------------------Programme_Pricipal-----------------------------#
#createdb()

drop_tables()
time.sleep(5)
create_tables()
time.sleep(5)

print''
print "Station meteo Eixa6 Informatique"
print "Connexion au port %s..." % port
ser = serial.Serial(port, 9600) #connexion serial
if ser!='' :
    print "Connexion effectue !"
else :
    print "Connexion refusee !"
    print "                    "
function_principal(last_date,date2)
	


