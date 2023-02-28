(:*******************************************************:)
(:Test: op-add-dayTimeDuration-to-time-10                :)
(:Written By: Carmelo Montanez                           :)
(:Date: July 1, 2005                                     :)
(:Purpose: Evaluates The "add-dayTimeDuration-to-time" function used  :)
(:together with an "or" expression.                      :)
(: Uses the "fn:string" function to account for new EBV rules. :)
(:*******************************************************:)
 
fn:string((xs:time("02:03:01Z") + xs:dayTimeDuration("P03DT01H04M"))) or fn:string((xs:time("02:03:01Z") + xs:dayTimeDuration("P01DT01H03M")))