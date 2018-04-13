#pragma once

// global staic variable can be contained multiple times
// if the global variable without 'static' in header, may occur
// 'multiple definition of a' when using it in other implementation files
static int a{1};
