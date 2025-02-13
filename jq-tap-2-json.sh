#!/bin/bash

jq -r '
  . |
      {
        test_suite: "pointers",  # Replace with your test suite name (or make it a parameter)
        test_cases: [
      . |
          if.ok then
            { name:.description, status: "passed" }
          else
            { name:.description, status: "failed", message:.diagnostic.text }
          end
        ]
      }
    ' "$1" # Use a parameter for input file
