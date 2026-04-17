#pragma once

// Each press shows one of these — cycles randomly
// 5 Star's famous tagline: "Do Nothing"

static const char* const RESPONSES[] = {
  "Do Nothing.",
  "Still nothing.\nPerfect.",
  "Why did you\npress that?",
  "5 STAR\napproves.",
  "Congrats.\nNothing happened.",
  "You pressed it.\nNothing changed.\nExcellent work.",
  "This is exactly\nwhat 5 Star\nwants from you.",
  "Press again\nfor more nothing.",
  "Achievement:\nDid Nothing.",
  "The button\ndoes nothing.\nYou knew that.",
  "Nothing to see.\nMove along.",
  "Error 404:\nPoint not found.",
  "You could be\neating a 5 Star\nright now.",
  "Doing nothing\nsince 1969.\nJust like you.",
  "Maximum effort.\nZero result.\nPerfect.",
  "The engineers\nwho built this\nalso did nothing.",
  "This button\ncost more than\nyour motivation.",
  "Scientifically\nproven to do\nabsolutely nothing.",
  "Still here?\nRespect.",
  "5 STAR MODE:\nACTIVATED\n(nothing happens)",
  "Your dedication\nto nothing is\ntruly inspiring.",
  "Press count\ndoes not matter.\nNothing matters.",
  "Loading...\n\n...nah.",
  "What were\nyou expecting\nexactly?",
  "Boredom level:\nCHARTED.",
};

static const int RESPONSE_COUNT = sizeof(RESPONSES) / sizeof(RESPONSES[0]);

// Milestone messages — shown at press count milestones
struct Milestone {
  int         count;
  const char* msg;
};

static const Milestone MILESTONES[] = {
  {   1,  "First press.\nHere we go." },
  {   5,  "5 presses.\n5 Star approved." },
  {  10,  "10 presses.\nSomeone stop you?" },
  {  25,  "25 presses.\nGet some help." },
  {  50,  "50 presses.\nYou need a 5 Star.\nSERIOUSLY." },
  { 100,  "100 presses.\nThis is your life\nnow. Congrats." },
  { 200,  "200 presses.\nCall your mum." },
  { 500,  "500 presses.\nLegend." },
};

static const int MILESTONE_COUNT = sizeof(MILESTONES) / sizeof(MILESTONES[0]);
