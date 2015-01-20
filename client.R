setwd("/home//fiedukow/repo/rbbcomp/")
source("RBBComp.R")

  # login with demo account - this should grant access to the "trial" track (for testing and debugging)
  result = Login("demoaccount", "demopassword");
  if (result == 0) { print("login() failed") }
  print("login successful");

  # request the tracks available to this user (this is optional)
  numTracks = NumberOfTracks();
  if (numTracks == 0) { print("numberOfTracks() failed") }
  for (i in 1:numTracks)
  {
    trackname = TrackName(i);
    if (trackname == "") { print("trackName() failed"); }
  }

  # set the track to "trial"
  result = SetTrack("trial");
  if (result == 0) { print("setTrack() failed"); }

  # obtain number of problems in the track
  numProblems = NumberOfProblems();
  if (numProblems == 0) { print("numberOfProblems() failed"); }

  # For demonstration purposes we optimize only the random problem in the track.
  problemID = round(runif(n = 1, min = 1, max = numProblems));
  result = SetProblem(problemID);
  if (result == 0) { print("setProblem() failed"); }
  print(paste0("Problem ID set to ", problemID));

  # obtain problem properties
  dim = Dimension();
  if (dim == 0) { print("dimension() failed"); }
  bud = Budget();
  if (bud == 0) { print("budget() failed"); }
  evals = evaluations();
  if (evals < 0) { print("evaluations() failed"); }
  print(paste0("problem dimension: ", dim));
  print(paste0("problem budget: ", bud));
  print(paste0("number of already used up evaluations: ", evals));

  # run the optimization loop
  bestValue = 1e100;
  points = matrix(runif((bud-evals)*dim),nrow=(bud-evals))
  values = Evaluate(points)
  bestValue = min(values)

  print(paste0("best value: ", bestValue));
