DROP DATABASE IF EXISTS fleet-manager-db;

CREATE SCHEMA if NOT EXISTS public;

CREATE table if not EXISTS Users (
  email VARCHAR(50) UNIQUE,
  password VARCHAR(250)
);

