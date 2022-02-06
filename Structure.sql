/**
 * Structure de la base de données CDAA 2021 - 2022
 *
 * Ne contient aucune données.
 *
*/

PRAGMA foreign_keys = false;

-- ----------------------------
-- Table structure for contact
-- ----------------------------
DROP TABLE IF EXISTS "contact";
CREATE TABLE "contact" (
  "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  "first_name" TEXT NOT NULL,
  "last_name" TEXT NOT NULL,
  "company" TEXT,
  "email" TEXT,
  "phone" TEXT,
  "creation_date" TEXT NOT NULL,
  "note" TEXT
);

-- ----------------------------
-- Auto increment value for contact
-- ----------------------------
UPDATE "sqlite_sequence" SET seq = 0 WHERE name = 'contact';


-- ----------------------------
-- Table structure for interaction
-- ----------------------------
DROP TABLE IF EXISTS "interaction";
CREATE TABLE "interaction" (
  "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  "owner_id" INTEGER NOT NULL,
  "type" INTEGER NOT NULL,
  "description" TEXT,
  "date" TEXT NOT NULL,
  CONSTRAINT "owner_interaction" FOREIGN KEY ("owner_id") REFERENCES "contact" ("id") ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Auto increment value for interaction
-- ----------------------------
UPDATE "sqlite_sequence" SET seq = 0 WHERE name = 'interaction';


-- ----------------------------
-- Table structure for todo
-- ----------------------------
DROP TABLE IF EXISTS "todo";
CREATE TABLE "todo" (
  "id" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
  "owner_id" INTEGER NOT NULL,
  "description" TEXT NOT NULL,
  "date" TEXT NOT NULL,
  CONSTRAINT "Owner_todo" FOREIGN KEY ("owner_id") REFERENCES "contact" ("id") ON DELETE NO ACTION ON UPDATE NO ACTION
);

-- ----------------------------
-- Auto increment value for todo
-- ----------------------------
UPDATE "sqlite_sequence" SET seq = 0 WHERE name = 'todo';


PRAGMA foreign_keys = true;
