(:*******************************************************:)
(: Test: K-ForExprWithout-50                             :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Ensure scanners/parsers accept small QNames in for-expressions. :)
(:*******************************************************:)
1 eq (for $a in 1 return $a)