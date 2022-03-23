/- Remove the placeholder and complete the following proofs -/
open classical

variables A B C : Prop
variables p q r : Prop

-- 1
example : A ∨ B → B ∨ A :=
  assume LHS : A ∨ B, show (B ∨ A), 
    from or.elim LHS
    (assume Ha : A, show B ∨ A, from or.inr Ha)
    (assume Hb : B, show B ∨ A, from or.inl Hb)

-- 2
example : A ∧ (B ∨ C) → (A ∧ B) ∨ (A ∧ C) := 
  assume LHS : A ∧ (B ∨ C),
  have Ha : A, from and.left LHS,
    show((A ∧ B) ∨ (A ∧ C)), from
      or.elim (and.right LHS)
        (assume Hb : B,
          show (A ∧ B) ∨ (A ∧ C), from or.inl (and.intro Ha Hb))
        (assume Hc : C,
          show (A ∧ B) ∨ (A ∧ C), from or.inr (and.intro Ha Hc))

-- 3
lemma deMorganRIL : ¬A ∧ ¬B → ¬(A ∨ B) := 
  assume LHS : ¬A ∧ ¬B, show ¬(A ∨ B), from
    have nA : ¬A, from and.left LHS,
    have nB : ¬B, from and.right LHS, 
    show ¬(A ∨ B), from (
      assume hAB: A ∨ B,
      show false, from
        or.elim hAB
          (assume hA : A, show false, from nA hA)
          (assume hB : B, show false, from nB hB)
    )

lemma deMorganLIR : ¬(A ∨ B) → ¬A ∧ ¬B := 
  assume LHS : ¬(A ∨ B), show ¬A ∧ ¬B, from
    have nA : ¬A, from (
      assume hA: A, 
      show false, from
        have hAB: A ∨ B, from or.inl hA,
        show false, from LHS hAB
    ),
    have nB : ¬B, from (
      assume hB: B, 
      show false, from
        have hAB: A ∨ B, from or.inr hB,
        show false, from LHS hAB
    ),
    show (¬A ∧ ¬ B), from and.intro nA nB

example : ¬(A ∨ B) ↔ ¬A ∧ ¬B := 
  iff.intro (deMorganLIR A B) (deMorganRIL A B)

-- 4
lemma contra : (¬A → ¬B) → (B → A) :=
  assume LHS : (¬A → ¬B), show (B → A), from
    assume H : B, show A, from
      by_contradiction (
        assume nA: ¬ A,
            have nB : ¬ B, from LHS nA,
            show false, from nB H
      )

example : ((p → q) ∧ (¬r → ¬q)) → (p → r) := 
  assume LHS : ((p → q) ∧ (¬r → ¬q)), show (p → r), from
    have Hpq : (p → q), from and.left LHS,
    have Hnrnq : (¬r → ¬q), from and.right LHS,
    have Hqr : (q → r), from (contra r q) (Hnrnq),
      assume hp : p, show r, from
        have Hq : q, from Hpq hp,
        show r, from Hqr Hq
