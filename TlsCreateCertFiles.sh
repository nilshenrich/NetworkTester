#!/bin/bash

# Recreate directories
rm -r keys/
mkdir -p keys/ca
mkdir -p keys/listener
mkdir -p keys/client

# Create CA key and certificate
openssl genrsa -out keys/ca/ca.key 2048
openssl req -new -x509 -days 36500 -key keys/ca/ca.key -out keys/ca/ca.crt -subj "/C=DE/ST=Baden-Wuerttemberg/L=Stuttgart/O=NetworkTester/OU=CA/CN=localhost"

# Create listener key and certificate signed by CA
openssl genrsa -out keys/listener/listener.key 2048
openssl req -new -key keys/listener/listener.key -out keys/listener/listener.csr -subj "/C=DE/ST=Baden-Wuerttemberg/L=Stuttgart/O=NetworkTester/OU=Listener/CN=localhost"
openssl x509 -req -days 36500 -in keys/listener/listener.csr -CA keys/ca/ca.crt -CAkey keys/ca/ca.key -CAcreateserial -out keys/listener/listener.crt

# Create client key and certificate signed by CA
openssl genrsa -out keys/client/client.key 2048
openssl req -new -key keys/client/client.key -out keys/client/client.csr -subj "/C=DE/ST=Baden-Wuerttemberg/L=Stuttgart/O=NetworkTester/OU=Client/CN=localhost"
openssl x509 -req -days 36500 -in keys/client/client.csr -CA keys/ca/ca.crt -CAkey keys/ca/ca.key -CAcreateserial -out keys/client/client.crt
