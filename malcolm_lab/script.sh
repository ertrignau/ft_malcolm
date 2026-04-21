#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR"

echo "[1] Starting lab..."
sudo docker compose up -d --build

echo "[2] Waiting for containers to be ready..."
sleep 3

echo "[3] Getting container IPs..."
GATEWAY_IP=$(sudo docker inspect gateaway --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}')
VICTIM_IP=$(sudo docker inspect victim --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}')
ATTACKER_IP=$(sudo docker inspect attacker --format='{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}')
echo "Gateway IP: $GATEWAY_IP"
echo "Victim IP: $VICTIM_IP"
echo "Attacker IP: $ATTACKER_IP"

echo "[4] Starting attacker..."
sudo docker exec attacker ./ft_malcolm $GATEWAY_IP aa:bb:cc:dd:ee:ff $VICTIM_IP 02:42:0a:00:64:01 &
ATTACKER_PID=$!

sleep 2

echo "[5] Victim pings gateway..."
sudo docker exec victim ping -c 1 $GATEWAY_IP

sleep 1

echo "[6] Check ARP table..."
sudo docker exec victim ip neigh

echo ""
echo "[✓] Test complete! Attacker PID: $ATTACKER_PID"
echo "To stop: kill $ATTACKER_PID && sudo docker compose down"
