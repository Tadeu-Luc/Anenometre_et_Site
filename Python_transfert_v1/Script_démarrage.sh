
source venv/bin/activate #active l'environnement virtuel.
trap 'kill $(jobs -p)' SIGINT SIGTERM #arrete toutes les taches en cours.

python Fonctionnel.py & #Demarre les 2 programmes python
python Serveur.py
